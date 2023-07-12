/*
 * PacketEnum.c
 *
 *  Created on: Jul. 3, 2023
 *      Author: Saksham Puri
 */

// Includes----------------------------------------------------------
// Include header libraries for commands, functions, and pin Names
#include "MemoryUtilities.h"


// Functions----------------------------------------------------------
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

	//TEMPORARY ADDRESS VARIABLE TO REPLACE CIRCULAR BUFFER
	uint8_t addr[3] = {0};

	char buffer[100] = {0};

	//Set Chip select to LOW and read from the address and store data in given buffer
	PULL_CS();
	HAL_SPI_Transmit(hspi1, (uint8_t*) &FLASH_READ, 1, 100);
	HAL_SPI_Transmit(hspi1, (uint8_t*) &addr, 3, 100);
	HAL_SPI_Receive(hspi1, (uint8_t*) spiRxBuffer, 100, 100);
	SET_CS();

	strcpy((char*) buffer, spiRxBuffer);

	return 0;
}
