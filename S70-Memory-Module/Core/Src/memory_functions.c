/*
 * memory_functions.c
 *
 *  Created on: Mar 22, 2024
 *      Author: Saksham Puri
 */

// -----------------------------INCLUDES-----------------------------
#include <memory_functions.h>
#include <debug_utilities.h>

// -----------------------------VARIABLES-----------------------------

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
void LFS_Config() {
	// block device operations
	cfg.read = block_device_read;
	cfg.prog = block_device_prog;
	cfg.erase = block_device_erase;
	cfg.sync = block_device_sync;

	// block device configuration
	cfg.read_size = 512;
	cfg.prog_size = 512;
	cfg.block_size = 8192;
	cfg.block_count = 8192;
	cfg.block_cycles = 500; // ASK ABOUT THIS (HOW FREQUENT ARE WE USING THE MODULE)
	cfg.cache_size = 512; // DO WE NEED CACHE SIZE (NOT SURE IF THIS IS NEEDED VALUE)
	cfg.lookahead_size = 512;
//	cfg.compact_thresh = 0; // Defaults to ~88% block_size when zero (lfs.h, line 232)

	cfg.read_buffer = lfs_read_buf;
	cfg.prog_buffer = lfs_prog_buf;
}

int block_device_read(const struct lfs_config *c, lfs_block_t block,
		lfs_off_t off, void *buffer, lfs_size_t size) {

	return READ_LFS(hspi_ptr, (uint8_t*) buffer, (block * c->block_size + off),
			size);
}

int block_device_prog(const struct lfs_config *c, lfs_block_t block,
		lfs_off_t off, const void *buffer, lfs_size_t size) {
	return WRITE_LFS(hspi_ptr, (uint8_t*) buffer, (block * c->block_size + off),
			size);
}

int block_device_erase(const struct lfs_config *c, lfs_block_t block) {
	MEM_CLEAR_LFS(hspi_ptr, block * c->block_size);
	return 0;
}

int block_device_sync(const struct lfs_config *c) {
	return 0;
}

// -----------------------------FUNCTIONS-----------------------------

void INITIALIZE(SPI_HandleTypeDef *ptr) {
	LFS_Config();
	LFS_initialized = 1;
	hspi_ptr = ptr;
}

int8_t MOUNT() {
	if (LFS_initialized && !mounted) {
		// Check if LittleFS successfully mounted
		int8_t result = lfs_mount(&lfs, &cfg);
		if (result < 0) {
			PRINT_STRING_UART("Mounting Unsuccessful", 1);
			return result;
		} else {
			PRINT_STRING_UART("Mounting Successful", 1);
			mounted = 1;
			return 0;
		}
	}
	return -1;
}

int8_t FORCE_MOUNT() {
	if (LFS_initialized && !mounted) {
		// Check if LittleFS successfully mounted
		int8_t result = MOUNT();

		//If it doesn't work, try formatting the memory, and mounting again
		if (result < 0) {
			result = FORMAT();
			if (result < 0)
				return result;

			result = MOUNT();
			if (result < 0)
				return result;
		}
		return 0;
	}
	return -1;
}

int8_t UNMOUNT() {
	if (LFS_initialized && mounted) {
		//Unmount LittleFS to release any resources used by LittleFS
		int8_t result = lfs_unmount(&lfs);
		if (result < 0) {
			PRINT_STRING_UART("Error Un-mounting!", 1);
			return result;
		} else {
			PRINT_STRING_UART("Successfully Un-mounted LittleFS!", 1);
			return result;
		}
	} return -1;
}

int8_t FORMAT() {
	if (LFS_initialized) {
		int8_t result = lfs_format(&lfs, &cfg);
		if (result < 0) {
			PRINT_STRING_UART("Error Formatting!", 1);
			return result;
		} else {
			PRINT_STRING_UART("Formatting! Successful", 1);
			return result;
		}
	}
	return -1;
}

void LIST_DIRECTORY() {

}

void REMOVE_FILE() {

}

void MAKE_DIRECTORY() {

}

void MOVE_DIRECTORY() {

}

int8_t WRITE_FILE(char *file_name, void *write_buffer, uint32_t size) {

	int8_t result = lfs_file_open(&lfs, &file, file_name,
			LFS_O_WRONLY | LFS_O_CREAT);
	if (result < 0) {
		PRINT_STRING_UART("Error Opening / Creating a File!", 1);
		return result;
	} else {
		PRINT_STRING_UART("Opened / Created a file named: ", 0);
		PRINT_STRING_UART(file_name, 1);

		// Write defined data to file
		result = lfs_file_write(&lfs, &file, write_buffer, size);
		if (result < 0) {
			PRINT_STRING_UART("Error Writing to File!", 1);
			return result;
		} else {
			PRINT_STRING_UART("Successfully wrote data to file!", 1);

			// Close the File, the storage is not updated until the file is closed successfully
			result = lfs_file_close(&lfs, &file);
			if (result < 0) {
				PRINT_STRING_UART("Error Closing the File!", 1);
				return result;
			} else {
				PRINT_STRING_UART("Successfully closed the File!", 1);
				return result;
			}
		}
	}
}

int8_t READ_FILE(char *file_name, void *read_buffer, uint32_t size) {
	int8_t result = lfs_file_open(&lfs, &file, file_name,
			LFS_O_RDONLY);
	if (result < 0) {
		PRINT_STRING_UART("Error Opening / Creating a File!", 1);
		return result;
	} else {
		PRINT_STRING_UART("Opened / Created a file named: ", 0);
		PRINT_STRING_UART(file_name, 1);

		// Write defined data to file
		result = lfs_file_read(&lfs, &file, read_buffer, size);
		if (result < 0) {
			PRINT_STRING_UART("Error Reading File!", 1);
			return result;
		} else {
			PRINT_STRING_UART("Successfully read data to file!", 1);

			// Close the File, the storage is not updated until the file is closed successfully
			result = lfs_file_close(&lfs, &file);
			if (result < 0) {
				PRINT_STRING_UART("Error Closing the File!", 1);
				return result;
			} else {
				PRINT_STRING_UART("Successfully closed the File!", 1);
				return result;
			}
		}
	}
}
