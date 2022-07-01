/*
 * uart.h
 *
 *  Created on: Dec 28, 2021
 *      Author: Matthew
 */

#ifndef INC_UART_H_
#define INC_UART_H_

/**
 * Configures the clock. This was an auto-built function (I think).
 */
void SystemClock_Config(void);

/**
 * Function that handles all UART initialization.
 */
void startUart();

/**
 * Function that transmits a message via UART. It takes in the message as a char pointer and an
 * integer representing the length of the char.
 */
void sendUartMessage(char* message, int length);

#endif /* INC_UART_H_ */
