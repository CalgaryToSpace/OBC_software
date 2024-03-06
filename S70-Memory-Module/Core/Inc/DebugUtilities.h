/*
 * DebugUtilities.h
 *
 *  Created on: Jul. 10, 2023
 *      Author: Saksham Puri
 */

#ifndef INC_DEBUGUTILITIES_H_
#define INC_DEBUGUTILITIES_H_

#include "MemoryUtilities.h"
#include "main.h"

extern UART_HandleTypeDef huart1; // Declare huart1 as an external variable

void PRINT_STRING_UART(void *);
void PRINT_NEW_LINE();

#endif /* INC_DEBUGUTILITIES_H_ */
