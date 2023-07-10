/*
 * PacketWrite.c
 *
 *  Created on: Jul. 4, 2023
 *      Author: Saksham Puri
 */

// Includes----------------------------------------------------------
// Include header libraries for commands, functions, and pin Names
#include "MemoryUtilities.h"

// Include string header library to use strcpy
#include <string.h>

// Functions----------------------------------------------------------
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
uint8_t WRITE(SPI_HandleTypeDef hspi1, void * packetBuffer) {
	// Buffers for transmitting data, and receiving status register data
	char spiTxBuffer[100] = {0};
	char statusRegBuffer[100] = {0};

	//Enable WREN Command, so that we can write to the memory module
	ENABLE_WREN(hspi1);

	//Copy the passed buffer data to a char buffer
	strcpy((char*) spiTxBuffer, packetBuffer);

	//TEMPORARY ADDRESS VARIABLE TO REPLACE CIRCULAR BUFFER
	uint8_t addr[3] = {0};

	//Transmit the Data to the Memory Module
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, (uint8_t*) &FLASH_WRITE, 1, 100);
	HAL_SPI_Transmit(&hspi1, (uint8_t*) &addr, 3, 100);
	HAL_SPI_Transmit(&hspi1, (uint8_t*) &spiTxBuffer, 100, 100);
	SET_CS();

	//Stay in the While loop until writing isn't done
	uint8_t wip = 1;
	while (wip) {
		READ_STATUS_REGISTER(hspi1, statusRegBuffer);
		wip = statusRegBuffer[0] & 1;
	}

	return 0;
}
