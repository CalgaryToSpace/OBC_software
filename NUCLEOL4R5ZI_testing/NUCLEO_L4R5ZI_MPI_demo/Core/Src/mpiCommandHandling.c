/*
 * mpiCommandHandling.c
 *
 */
#include <mpiCommandHandling.h>
#include <stdio.h>
#include "main.h"

// This function sends commands to the MPI. Parameters argument is set to NULL when no parameters are required as part of a command.
// TODO: Add error check
uint8_t sendTelecommand(uint8_t commandCode, uint8_t parameters){

	uint8_t UART1_txBuffer[160] = {0};
	// Turn on frame transmitting TC
	UART1_txBuffer[0] = 0x54;
	UART1_txBuffer[1] = 0x43;
	UART1_txBuffer[2] = commandCode;

	// Command with no parameters detected: Transmit command
	if(parameters != 0xFF){
		UART1_txBuffer[3] = parameters;
	}

	// Transmit command
	HAL_UART_Transmit(&huart1, (uint8_t *)UART1_txBuffer, strlen((char*)UART1_txBuffer), 100);

	return 1;
}




