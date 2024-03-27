/*
 * send.h
 *
 *  Created on: Jul 7, 2022
 *      Author: mswel
 */

#ifndef INC_SEND_H_
#define INC_SEND_H_

#include "main.h"
#include <string.h>
#include "stm32l4xx_hal.h"

extern UART_HandleTypeDef hlpuart1;
extern UART_HandleTypeDef huart3;

void sendGpsCommand(char* command);

#endif /* INC_SEND_H_ */
