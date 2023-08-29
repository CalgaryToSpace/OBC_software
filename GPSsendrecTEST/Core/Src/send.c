/*
 * send.c
 *
 *
 *  Created on: Jul 7, 2022
 *      Author: mswel
 */

#include "send.h"

void sendGpsCommand(char* command){
	/**
	 * Okay let's do this one last time
	 *
	 * method input is string of command
	 *
	 * Need to transmit command onto USART 3 port
	 */

	// first command string will be transmitted to virtual com on hlpuart1 to verify it was able to send
//	HAL_UART_Transmit(&hlpuart1, (uint8_t*)command, strlen(command), HAL_MAX_DELAY);
	// ** DELETE ABOVE LINE AFTER TESTING IS COMPLETE **
	// then it will be sent to GPS via USART3
//	HAL_UART_Transmit(&huart3, (uint8_t*)command, strlen(command), HAL_MAX_DELAY);

}
