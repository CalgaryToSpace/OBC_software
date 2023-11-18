/*
 * mpiCommands.h
 *
 *  Created on: Nov 17, 2023
 *      Author: vaibh
 */

#ifndef INC_MPICOMMANDHANDLING_H_
#define INC_MPICOMMANDHANDLING_H_
#include <main.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>


uint8_t sendTelecommand(uint8_t commandCode, uint8_t parameters, UART_HandleTypeDef *huart);


#endif /* INC_MPICOMMANDHANDLING_H_ */
