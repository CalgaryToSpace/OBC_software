/**
 * memory_utilities.c
 *
 * Created on: May 2, 2024
 *     Author: Saksham Puri
 */

/*-----------------------------INCLUDES-----------------------------*/
#include "memory_utilities.h"
#include "debug_uart.h"
/*-----------------------------VARIABLES-----------------------------*/

// Memory Clear Flag for WRITE function to know when to clear flag
uint8_t clearFlag = 1;

uint8_t LFS_initialized = 0;
uint8_t mounted = 0;

// LittleFS variables
lfs_t lfs;
lfs_file_t file;
struct lfs_config cfg;

// LittleFS Buffers for reading and writing
uint8_t lfs_read_buf[512];
uint8_t lfs_prog_buf[512];

SPI_HandleTypeDef *hspi_ptr;

// -----------------------------SETUP FUNCTIONS-----------------------------

/**
 * @brief Initialize LittleFS configurations
 * @param None
 * @retval None
 */
void LFS_Config()
{
    // block device operations
    cfg.read = block_device_read;
    cfg.prog = block_device_prog;
    cfg.erase = block_device_erase;
    cfg.sync = block_device_sync;

    // block device configuration
    cfg.read_size = 512;
    cfg.prog_size = 512;
    cfg.block_size = 262144;
    cfg.block_count = 256;
    cfg.block_cycles = 100; // ASK ABOUT THIS (HOW FREQUENT ARE WE USING THE MODULE)
    cfg.cache_size = 512;
    cfg.lookahead_size = 16;
    cfg.compact_thresh = -1; // Defaults to ~88% block_size when zero (lfs.h, line 232)

    cfg.read_buffer = lfs_read_buf;
    cfg.prog_buffer = lfs_prog_buf;
}

int block_device_read(const struct lfs_config *c, lfs_block_t block,
                      lfs_off_t off, void *buffer, lfs_size_t size)
{

    return READ_LFS(hspi_ptr, (uint8_t *)buffer, (block * c->block_size + off),
                    size);
}

int block_device_prog(const struct lfs_config *c, lfs_block_t block,
                      lfs_off_t off, const void *buffer, lfs_size_t size)
{
    return WRITE_LFS(hspi_ptr, (uint8_t *)buffer, (block * c->block_size + off),
                     size);
}

int block_device_erase(const struct lfs_config *c, lfs_block_t block)
{
    MEM_CLEAR_LFS(hspi_ptr, block * c->block_size);
    //	MEM_CLEAR_LFS(hspi_ptr, block * c->block_size);
    return 0;
}

int block_device_sync(const struct lfs_config *c)
{
    return 0;
}

// -----------------------------FUNCTIONS-----------------------------

/*
 * Chip Select set to LOW
 */
void PULL_CS()
{
    HAL_GPIO_WritePin(PIN_SCI_NCS_FLASH_0_GPIO_Port, PIN_SCI_NCS_FLASH_0_Pin, GPIO_PIN_RESET); // LSB
}

/*
 * Chip Select set to HIGH
 * This is the default state of the CS
 */
void SET_CS()
{
    HAL_GPIO_WritePin(PIN_SCI_NCS_FLASH_0_GPIO_Port, PIN_SCI_NCS_FLASH_0_Pin, GPIO_PIN_SET);
}

/*
 * @param Takes any type of array/pointer, always converts to uint8_t pointer
 * @return Nothing, Reads Status Register, stores value in param
 * Sets Decoder Inputs BeforeHand
 * Pull All Decoder Inputs High After
 *
 */
void READ_STATUS_REGISTER(SPI_HandleTypeDef *hspi1, uint8_t *rxBuf)
{
    PULL_CS();
    HAL_SPI_Transmit(hspi1, (uint8_t *)&FLASH_STATREG1, 1, 100);
    HAL_SPI_Receive(hspi1, (uint8_t *)rxBuf, 1, 100);
    SET_CS();
}

/*
 * Just Transmit WREN Command
 * Sets Decoder Inputs beforehand
 * Pull all Decoder Inputs High After
 */
void ENABLE_WREN(SPI_HandleTypeDef *hspi1)
{
    uint8_t statusRegBuffer[1] = {0};
    READ_STATUS_REGISTER(hspi1, statusRegBuffer);

    PULL_CS();
    if (HAL_SPI_Transmit(hspi1, (uint8_t *)&FLASH_WREN, 1, HAL_MAX_DELAY) != HAL_OK)
    {
        debug_uart_print_str_mem("Timeout when enabling WREN\n");
    }
    SET_CS();

    uint8_t wip = 1;
    while (wip)
    {
        READ_STATUS_REGISTER(hspi1, statusRegBuffer);
        wip = statusRegBuffer[0] & 1;
    }
}

/*
 * Just Transmit WRDI Command
 * As noted  in Section 9.3.9 of the Manual,
 * ALL Chip Selects must be pulled high in order for this command
 * to go through
 */
void ENABLE_WRDI(SPI_HandleTypeDef *hspi1)
{
    SET_CS();
    HAL_SPI_Transmit(hspi1, (uint8_t *)&FLASH_WRDI, 1, 100);

    uint8_t statusRegBuffer[1] = {0};

    // Stay in the While loop until writing isn't done
    uint8_t wel = 1;
    while (wel)
    {
        READ_STATUS_REGISTER(hspi1, statusRegBuffer);
        wel = statusRegBuffer[0] & 2;
    }
}

/*
 * @param Takes a void pointer which is converted to uint8_t used as an address
 * The function takes an address and clears the memory in that address
 * We wait until the clearing is done and then end the function
 */
void MEM_CLEAR_LFS(SPI_HandleTypeDef *ptr_hspi1, lfs_block_t block)
{
    uint8_t addr[3] =
        {(block >> 16) & 0xFF, (block >> 8) & 0xFF, block & 0xFF};
    ENABLE_WREN(ptr_hspi1);

    PULL_CS();
    HAL_SPI_Transmit(ptr_hspi1, (uint8_t *)&FLASH_SECTOR_ERASE, 1, 100);
    HAL_SPI_Transmit(ptr_hspi1, (uint8_t *)addr, 3, 100);
    SET_CS();

    uint8_t statusRegBuffer[1] = {0};

    // Stay in the While loop until writing isn't done
    uint8_t wip = 1;
    uint8_t err = 0;
    while (wip)
    {
        READ_STATUS_REGISTER(ptr_hspi1, statusRegBuffer);
        wip = statusRegBuffer[0] & 1;
        err = statusRegBuffer[0] & 0b01000000;
        if (err == 1)
        {
            debug_uart_print_str_mem("Error during Erasing\n");
        }
    }
}

/**
 * This function writes data into memory using ADDRESS from LittleFS
 * and stays in the function until the writing is done.
 * Precondition of running WREN command is done within the function
 *
 * @param - SPI_HandleTypeDef hspi1 holds SPI protocol data for communication
 * 			void * packetBuffer holds the buffer to write to memory
 *
 * @return - 0 if written successfully
 * 			 -1 if an error occurred during writing to memory
 */
uint8_t WRITE_LFS(SPI_HandleTypeDef *hspi1, uint8_t *packetBuffer,
                  lfs_block_t block, lfs_size_t size)
{
    uint8_t addr[3] =
        {(block >> 16) & 0xFF, (block >> 8) & 0xFF, block & 0xFF};

    // Buffer for receiving status register data
    uint8_t statusRegBuffer[1] = {0};

    // Enable WREN Command, so that we can write to the memory module
    ENABLE_WREN(hspi1);

    // Transmit the Data to the Memory Module
    PULL_CS();
    HAL_SPI_Transmit(hspi1, (uint8_t *)&FLASH_WRITE, 1, 100);
    HAL_SPI_Transmit(hspi1, (uint8_t *)addr, 3, 100);
    HAL_SPI_Transmit(hspi1, (uint8_t *)packetBuffer, size, 100);
    SET_CS();

    // Stay in the While loop until writing isn't done
    uint8_t wip = 1;
    uint8_t err = 0;
    while (wip)
    {
        READ_STATUS_REGISTER(hspi1, statusRegBuffer);
        wip = statusRegBuffer[0] & 1;
        err = statusRegBuffer[0] & 0b01000000;

        // If error while writing break from loop
        if (err == 1)
        {
            err = -1;
            break;
        }
    }

    // return err value
    return err;
}

/**
 * This function reads data from memory using ADDRESS FROM CIRCULAR BUFFER
 * and stays in the function until the reading is done.
 * The Chip Select is done within the function to ensure READ is done
 *
 * @param - SPI_HandleTypeDef hspi1 holds SPI protocol data for communication
 * 			void * spiRxBuffer is the buffer data is going to be put into after reading
 *
 * @return - 0 if read successfully
 * 			 1 if an error occurred during writing to memory
 */
uint8_t READ_LFS(SPI_HandleTypeDef *hspi1, uint8_t *spiRxBuffer,
                 lfs_block_t block, lfs_size_t size)
{
    uint8_t addr[3] =
        {(block >> 16) & 0xFF, (block >> 8) & 0xFF, block & 0xFF};

    // Set Chip select to LOW and read from the address and store data in given buffer
    PULL_CS();
    HAL_SPI_Transmit(hspi1, (uint8_t *)&FLASH_READ, 1, 100);
    HAL_SPI_Transmit(hspi1, (uint8_t *)addr, 3, 100);
    HAL_SPI_Receive(hspi1, (uint8_t *)spiRxBuffer, size, 100);
    SET_CS();

    // Haven't yet implemented a way to check any errors while reading data from memory
    return 0;
}

void INITIALIZE(SPI_HandleTypeDef *ptr)
{
    LFS_Config();
    LFS_initialized = 1;
    hspi_ptr = ptr;
}

int8_t MOUNT()
{
    if (LFS_initialized && !mounted)
    {
        // Check if LittleFS successfully mounted
        int8_t result = lfs_mount(&lfs, &cfg);
        if (result < 0)
        {
            debug_uart_print_str_mem("Mounting Unsuccessful\n");
            return result;
        }
        else
        {
            debug_uart_print_str_mem("Mounting Successful\n");
            mounted = 1;
            return 0;
        }
    }
    debug_uart_print_str_mem("LittleFS not Initialized or already mounted\n");
    return -1;
}

int8_t FORCE_MOUNT()
{
    if (LFS_initialized && !mounted)
    {
        // Check if LittleFS successfully mounted
        int8_t result = MOUNT();

        // If it doesn't work, try formatting the memory, and mounting again
        if (result < 0)
        {
            result = FORMAT();
            if (result < 0)
                return result;

            result = MOUNT();
            if (result < 0)
                return result;
        }
        return 0;
    }
    debug_uart_print_str_mem("LittleFS not Initialized or already mounted\n");
    return -1;
}

int8_t UNMOUNT()
{
    if (LFS_initialized && mounted)
    {
        // Unmount LittleFS to release any resources used by LittleFS
        int8_t result = lfs_unmount(&lfs);
        if (result < 0)
        {
            debug_uart_print_str_mem("Error Un-mounting!\n");
            return result;
        }
        else
        {
            debug_uart_print_str_mem("Successfully Un-mounted LittleFS!\n");
            mounted = 0;
            return result;
        }
    }
    debug_uart_print_str_mem("LittleFS not Initialized or not mounted\n");
    return -1;
}

int8_t FORMAT()
{
    if (LFS_initialized)
    {
        int8_t result = lfs_format(&lfs, &cfg);
        if (result < 0)
        {
            debug_uart_print_str_mem("Error Formatting!\n");
            return result;
        }
        else
        {
            debug_uart_print_str_mem("Formatting Successful!\n");
            return result;
        }
    }
    debug_uart_print_str_mem("LittleFS not Initialized\n");
    return -1;
}

void LIST_DIRECTORY()
{
}

void REMOVE_FILE()
{
}

void MAKE_DIRECTORY()
{
}

void MOVE_DIRECTORY()
{
}

int8_t WRITE_FILE(char *file_name, void *write_buffer, uint32_t size)
{

    int8_t result = lfs_file_open(&lfs, &file, file_name,
                                  LFS_O_WRONLY | LFS_O_CREAT);
    if (result < 0)
    {
        debug_uart_print_str_mem("Error Opening / Creating a File!\n");
        return result;
    }
    else
    {
        debug_uart_print_str_mem("Opened / Created a file named: \n");
        debug_uart_print_str_mem(file_name);

        // Write defined data to file
        result = lfs_file_write(&lfs, &file, write_buffer, size);
        if (result < 0)
        {
            debug_uart_print_str_mem("Error Writing to File!\n");
            return result;
        }
        else
        {
            debug_uart_print_str_mem("Successfully wrote data to file!\n");

            // Close the File, the storage is not updated until the file is closed successfully
            result = lfs_file_close(&lfs, &file);
            if (result < 0)
            {
                debug_uart_print_str_mem("Error Closing the File!\n");
                return result;
            }
            else
            {
                debug_uart_print_str_mem("Successfully closed the File!\n");
                return result;
            }
        }
    }
}

int8_t READ_FILE(char *file_name, void *read_buffer, uint32_t size)
{
    int8_t result = lfs_file_open(&lfs, &file, file_name,
                                  LFS_O_RDONLY | LFS_O_CREAT);
    if (result < 0)
    {
        debug_uart_print_str_mem("Error Opening / Creating a File!\n");
        return result;
    }
    else
    {
        debug_uart_print_str_mem("Opened / Created a file named: \n");
        debug_uart_print_str_mem(file_name);

        // Write defined data to file
        result = lfs_file_read(&lfs, &file, read_buffer, size);
        if (result < 0)
        {
            debug_uart_print_str_mem("Error Reading File!\n");
            return result;
        }
        else
        {
            debug_uart_print_str_mem("Successfully read file!\n");

            // Close the File, the storage is not updated until the file is closed successfully
            result = lfs_file_close(&lfs, &file);
            if (result < 0)
            {
                debug_uart_print_str_mem("Error Closing the File!\n");
                return result;
            }
            else
            {
                debug_uart_print_str_mem("Successfully closed the File!\n");
                return result;
            }
        }
    }
}