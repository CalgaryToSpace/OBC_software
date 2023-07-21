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
//uint8_t WRITE(SPI_HandleTypeDef *hspi1, uint8_t * packetBuffer) {
//	//TEMPORARY ADDRESS VARIABLE TO REPLACE CIRCULAR BUFFER
////	uint8_t addr[3] = {(cb.head >> 8) & 0xFF,(cb.head >> 4) & 0xFF, cb.head & 0xFF};
//	uint8_t addr[3] = {0x0};
//
////	if (cb.head % 256 == 0) {
////		//Clear the address where writing will be done
////		MEM_CLEAR(hspi1, addr);
////		MEM_CLEAR(hspi1, addr);
////	}
//
//	// Buffers for transmitting data, and receiving status register data
//	uint8_t spiTxBuffer[100] = {0};
//	uint8_t statusRegBuffer[50] = {0};
//
//	//Enable WREN Command, so that we can write to the memory module
//	ENABLE_WREN(hspi1);
//
//	READ_STATUS_REGISTER(hspi1, statusRegBuffer);
//
//	size_t packetSize = 0;
//	while (packetBuffer[packetSize] != '\0' && packetSize < sizeof(spiTxBuffer)) {
//	    spiTxBuffer[packetSize] = packetBuffer[packetSize];
//	    packetSize++;
//	}
//
////	//Copy the passed buffer data to a char buffer
////	strcpy((char*) spiTxBuffer, (char*) packetBuffer);
////
////	//Size of the packet
////	uint8_t packetSize = sizeof(spiTxBuffer);
//
//	//Transmit the Data to the Memory Module
//	PULL_CS();
//
//	HAL_SPI_Transmit(hspi1, (uint8_t*) &FLASH_WRITE, 1, 100);
//	HAL_SPI_Transmit(hspi1, (uint8_t*) &addr, 3, 100);
//	HAL_SPI_Transmit(hspi1, (uint8_t*) &spiTxBuffer, 100, 100);
//	SET_CS();
//
////	//Update the circular buffer
////	cb.tail = cb.head;
////	cb.head += packetSize;
//
//	//Stay in the While loop until writing isn't done
//	uint8_t wip = 1;
//	while (wip) {
//		READ_STATUS_REGISTER(hspi1, statusRegBuffer);
//		wip = statusRegBuffer[0] & 1;
//	}
//
//	return 0;
//}
