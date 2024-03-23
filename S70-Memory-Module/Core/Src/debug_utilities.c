/*
 * debug_utilities.c
 *
 *  Created on: Jul. 10, 2023
 *      Author: Saksham Puri
 */

// -----------------------------INCLUDES-----------------------------

// Includes Memory Utilities and String header files
#include <debug_utilities.h>
#include <memory_utilities.h>
#include "string.h"

// -----------------------------VARIABLES-----------------------------

// Huart1 to use the UART protocol for debugging purposes
UART_HandleTypeDef huart1;

// Variable to check if above UART variable has been initialized or not
uint8_t initialized = 0;

// -----------------------------FUNCTIONS-----------------------------

/**
 * @brief USART1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART1_UART_Init(void) {
	huart1.Instance = USART1;
	huart1.Init.BaudRate = 115200;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
	huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart1) != HAL_OK) {
		Error_Handler();
	}
	if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8)
			!= HAL_OK) {
		Error_Handler();
	}
	if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8)
			!= HAL_OK) {
		Error_Handler();
	}
	if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief Function to print a new line (\n) in UART
 * @param None
 * @retval None
 */
void PRINT_NEW_LINE() {
	char buf[] = "\r\n";
	HAL_UART_Transmit(&huart1, (uint8_t*) buf, strlen(buf), 100);
}

/**
 * @brief Function to print a given string to UART
 * @param *string, String that needs to be transmitted through UART
 * @param newLine, 1 if adding a \n after tranmitting string
 * @retval None
 */
void PRINT_STRING_UART(void *string, uint8_t newLine) {

	// If UART variable not initialized, initialize the variable
	if (initialized == 0) {
		MX_USART1_UART_Init();
		initialized = 1;
	}

	// Transmit the String through UART
	HAL_UART_Transmit(&huart1, (uint8_t*) string, strlen((char*) string), 100);

	// Transmit new Line if needed
	if (newLine) PRINT_NEW_LINE();
}
