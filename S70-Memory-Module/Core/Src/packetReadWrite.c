/*
 * packetReadWrite.c
 *
 *  Created on: Jul. 20, 2023
 *      Author: Saksham Puri
 */

// Includes----------------------------------------------------------
// Include header libraries for commands, functions, and pin Names
#include "MemoryUtilities.h"

// Include string header library to use strcpy
#include <string.h>

// Variables---------------------------------------------------------
// Circular buffer variable
CircularBuffer cb;

// Memory Clear Flag for WRITE function to know when to clear flag
uint8_t clearFlag = 1;

// Variable that keeps track of the number of bytes until next page
uint16_t bytesUntilNextPage = 512;

// Functions----------------------------------------------------------

//Initialize the head and tail for the Circular Buffer
void INITIALIZE() {
	cb.tail = 0x000000;
	cb.head = 0x000000;
}

/**
 * This function writes data into memory using ADDRESS FROM CIRCULAR BUFFER
 * and stays in the function until the writing is done.
 * Precondition of running WREN command is done within the function
 *
 * @param - SPI_HandleTypeDef hspi1 holds SPI protocol data for communication
 * 			void * packetBuffer holds the buffer to write to memory
 *
 * @return - 0 if written successfully
 * 			 1 if an error occurred during writing to memory
 */
uint8_t WRITE(SPI_HandleTypeDef *hspi1, uint8_t * packetBuffer) {
	uint8_t addr[3] = {(cb.head >> 16) & 0xFF,(cb.head >> 8) & 0xFF, cb.head & 0xFF};
//	uint8_t addr[3] = {0x00, 0x00, 0x00};

	// Buffers for transmitting data, and receiving status register data
	uint8_t spiTxBuffer[513] = {0};
	uint8_t backupBuffer[512] = {0};
	uint8_t statusRegBuffer[2] = {0};

	// Variable to store the packet size
	size_t packetSize = 0;

	// Variable used to store data in the backup buffer
	uint8_t backupIndex = 0;

	// Calculate the packet size while adding data to buffer as well as keep track of page overflow
	while (packetBuffer[packetSize] != '\0' && packetSize < sizeof(spiTxBuffer)) {
		if (bytesUntilNextPage == 0) {
			backupBuffer[backupIndex] = packetBuffer[packetSize];
			backupIndex++;
			packetSize++;
		} else {
			spiTxBuffer[packetSize] = packetBuffer[packetSize];
			packetSize++;
			bytesUntilNextPage--;
		}
	}

	// Set packet size to data size being written this iteration
	packetSize -= backupIndex;

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
	HAL_SPI_Transmit(hspi1, (uint8_t*) &spiTxBuffer, packetSize, 100);
	SET_CS();

	// Update the circular buffer
	cb.tail = cb.head;

	// If going over a sector, set clearFlag to 1 for next time
	if (cb.tail % 0x0003FFFF > (cb.head += packetSize) % 0x0003FFFF) {
		clearFlag = 1;
	}

	// Stay in the While loop until writing isn't done
	uint8_t wip = 1;
	uint8_t err = 0;
	while (wip) {
		READ_STATUS_REGISTER(hspi1, statusRegBuffer);
		wip = statusRegBuffer[0] & 1;
		err = statusRegBuffer[0] & 0b01000000;

		// If error while writing break from loop
		if (err == 1) {
			err = 1;
			break;
		}
	}

	// If we filled current page, reset bytesUntilNextPage variable
	if (bytesUntilNextPage == 0) {
		bytesUntilNextPage = 512;
	}

	// If not all data written to the memory yet
	if (backupIndex > 0) {
		WRITE(hspi1, backupBuffer);
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
uint8_t READ(SPI_HandleTypeDef *hspi1, uint8_t * spiRxBuffer) {
	uint8_t addr[3] = {(cb.tail >> 16) & 0xFF,(cb.tail >> 8) & 0xFF, cb.tail & 0xFF};
//	uint8_t addr[3] = {0x03, 0xFF, 0xFF};

	// Set Chip select to LOW and read from the address and store data in given buffer
	PULL_CS();
	HAL_SPI_Transmit(hspi1, (uint8_t*) &FLASH_READ, 1, 100);
	HAL_SPI_Transmit(hspi1, (uint8_t*) &addr, 3, 100);
	HAL_SPI_Receive(hspi1, (uint8_t*) spiRxBuffer, cb.head - cb.tail, 100);
	SET_CS();

	//Haven't yet implemented a way to check any errors while reading data from memory
	return 0;
}
