/*
 * MemoryUtilities.c
 *
 *  Created on: Jul. 4, 2023
 *      Author: Saksham Puri
 */

// Includes----------------------------------------------------------
// Include header libraries for commands, functions, and pin Names and debugging
#include <memory_utilities.h>
#include <memory_functions.h>
#include <debug_utilities.h>

// Memory Clear Flag for WRITE function to know when to clear flag
uint8_t clearFlag = 1;

/*
 * Chip Select set to LOW
 */
void PULL_CS() {
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET); // LSB
}

/*
 * Chip Select set to HIGH
 * This is the default state of the CS
 */
void SET_CS() {
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET);
}

/*
 * @param Takes any type of array/pointer, always converts to uint8_t pointer
 * @return Nothing, Reads Status Register, stores value in param
 * Sets Decoder Inputs BeforeHand
 * Pull All Decoder Inputs High After
 *
 */
void READ_STATUS_REGISTER(SPI_HandleTypeDef *hspi1, uint8_t *rxBuf) {
	PULL_CS();
	HAL_SPI_Transmit(hspi1, (uint8_t*) &FLASH_STATREG1, 1, 100);
	HAL_SPI_Receive(hspi1, (uint8_t*) rxBuf, 1, 100);
	SET_CS();
}

/*
 * Just Transmit WREN Command
 * Sets Decoder Inputs beforehand
 * Pull all Decoder Inputs High After
 */
void ENABLE_WREN(SPI_HandleTypeDef *hspi1) {
	PULL_CS();
	if (HAL_SPI_Transmit(hspi1, (uint8_t*) &FLASH_WREN, 1, HAL_MAX_DELAY) != HAL_OK) {
		PRINT_STRING_UART("Timeout when enabling WREN", 1);
	}
	SET_CS();

	uint8_t statusRegBuffer[10] = {0};

	uint8_t wip = 1;
	while (wip) {
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
void ENABLE_WRDI(SPI_HandleTypeDef *hspi1) {
	SET_CS();
	HAL_SPI_Transmit(hspi1, (uint8_t*) &FLASH_WRDI, 1, 100);

	uint8_t statusRegBuffer[50] = {0};

	//Stay in the While loop until writing isn't done
	uint8_t wel = 1;
	while (wel) {
		READ_STATUS_REGISTER(hspi1, statusRegBuffer);
		wel = statusRegBuffer[0] & 2;
	}
}

/*
 * @param Takes a void pointer which is converted to uint8_t used as an address
 * The function takes an address and clears the memory in that address
 * We wait until the clearing is done and then end the function
 */
void MEM_CLEAR(SPI_HandleTypeDef *ptr_hspi1, uint8_t * addr) {
	ENABLE_WREN(ptr_hspi1);

	uint8_t **ptr = &addr;

	PULL_CS();
	HAL_SPI_Transmit(ptr_hspi1, (uint8_t*)&FLASH_SECTOR_ERASE, 1, 100);
	HAL_SPI_Transmit(ptr_hspi1, (uint8_t*)*ptr, 3, 100);
	SET_CS();

	uint8_t statusRegBuffer[50] = {0};

	//Stay in the While loop until writing isn't done
	uint8_t wip = 1;
	uint8_t err = 0;
	while (wip) {
		READ_STATUS_REGISTER(ptr_hspi1, statusRegBuffer);
		wip = statusRegBuffer[0] & 1;
		err = statusRegBuffer[2] & 2;
		if (err == 1) {
			PRINT_STRING_UART("Error during Erasing", 1);
		}
	}
}

/*
 * @param Takes a void pointer which is converted to uint8_t used as an address
 * The function takes an address and clears the memory in that address
 * We wait until the clearing is done and then end the function
 */
void MEM_CLEAR_LFS(SPI_HandleTypeDef *ptr_hspi1, lfs_block_t block) {
	ENABLE_WREN(ptr_hspi1);

	PULL_CS();
	HAL_SPI_Transmit(ptr_hspi1, (uint8_t*)&FLASH_SECTOR_ERASE, 1, 100);
	HAL_SPI_Transmit(ptr_hspi1, (uint8_t*)block, 3, 100);
	SET_CS();

	uint8_t statusRegBuffer[50] = {0};

	//Stay in the While loop until writing isn't done
	uint8_t wip = 1;
	uint8_t err = 0;
	while (wip) {
		READ_STATUS_REGISTER(ptr_hspi1, statusRegBuffer);
		wip = statusRegBuffer[0] & 1;
		err = statusRegBuffer[2] & 2;
		if (err == 1) {
			PRINT_STRING_UART("Error during Erasing", 1);
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
uint8_t WRITE_LFS(SPI_HandleTypeDef *hspi1, uint8_t * packetBuffer, lfs_block_t block, lfs_size_t size) {
	uint8_t addr[3] = {(block >> 16) & 0xFF,(block >> 8) & 0xFF, block & 0xFF};

	// Buffer for receiving status register data
	uint8_t statusRegBuffer[1] = {0};

	// Clear the address where writing will be done when the clearFlag is 1
	if (clearFlag == 1) {
		clearFlag = 0;

		MEM_CLEAR(hspi1, addr);
		MEM_CLEAR(hspi1, addr);
	}

	// Enable WREN Command, so that we can write to the memory module
	ENABLE_WREN(hspi1);

	// Transmit the Data to the Memory Module
	PULL_CS();
	HAL_SPI_Transmit(hspi1, (uint8_t*) &FLASH_WRITE, 1, 100);
	HAL_SPI_Transmit(hspi1, (uint8_t*) &addr, 3, 100);
	HAL_SPI_Transmit(hspi1, (uint8_t*) packetBuffer, size, 100);
	SET_CS();

	// Stay in the While loop until writing isn't done
	uint8_t wip = 1;
	uint8_t err = 0;
	while (wip) {
		READ_STATUS_REGISTER(hspi1, statusRegBuffer);
		wip = statusRegBuffer[0] & 1;
		err = statusRegBuffer[0] & 0b01000000;

		// If error while writing break from loop
		if (err == 1) {
			err = -1;
			break;
		}
	}

	//return err value
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
uint8_t READ_LFS(SPI_HandleTypeDef *hspi1, uint8_t * spiRxBuffer, lfs_block_t block, lfs_size_t size) {
	uint8_t addr[3] = {(block >> 16) & 0xFF,(block >> 8) & 0xFF, block & 0xFF};

	// Set Chip select to LOW and read from the address and store data in given buffer
	PULL_CS();
	HAL_SPI_Transmit(hspi1, (uint8_t*) &FLASH_READ, 1, 100);
	HAL_SPI_Transmit(hspi1, (uint8_t*) &addr, 3, 100);
	HAL_SPI_Receive(hspi1, (uint8_t*) spiRxBuffer, size, 100);
	SET_CS();

	//Haven't yet implemented a way to check any errors while reading data from memory
	return 0;
}

