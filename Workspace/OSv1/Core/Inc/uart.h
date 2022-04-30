/*
 * uart.h
 *
 *  Created on: Dec 28, 2021
 *      Author: Matthew
 */

#ifndef INC_UART_H_
#define INC_UART_H_

// Configure the clock
void SystemClock_Config(void);

// Calls UART initialization functions
void startUart();

// Transmits a UART message of a set length
void sendUartMessage(char* message, int length);

#endif /* INC_UART_H_ */
