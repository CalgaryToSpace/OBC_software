/*
 * DebugUtilities.c
 *
 *  Created on: Jul. 10, 2023
 *      Author: Saksham Puri
 */

// Includes----------------------------------------------------------
// Includes Memory Utilities and String header files
#include "../Inc/MemoryUtilities.h"
#include "string.h"

// Variables---------------------------------------------------------
// huart1 to use the UART protocol for debugging purposes
UART_HandleTypeDef huart1;

//variable to check if above UART variable has been initialized or not
uint8_t initialized = 0;

// Functions----------------------------------------------------------

/**
 * @brief USART1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART1_UART_Init(void) {

	/* USER CODE BEGIN USART1_Init 0 */

	/* USER CODE END USART1_Init 0 */

	/* USER CODE BEGIN USART1_Init 1 */

	/* USER CODE END USART1_Init 1 */
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
	/* USER CODE BEGIN USART1_Init 2 */

	/* USER CODE END USART1_Init 2 */
}

//Function to print a new line (\n) in UART
void PRINT_NEW_LINE() {
	char buf[] = "\r\n";
	HAL_UART_Transmit(&huart1, (uint8_t*) buf, strlen(buf), 100);
}

//Function to print a given string to UART
void PRINT_STRING_UART(void *string) {

	//If UART variable not initialized, initialize the variable
	if (initialized == 0) {
		MX_USART1_UART_Init();
		initialized = 1;
	}

//	char *buff = (char*) string;
	HAL_UART_Transmit(&huart1, (uint8_t*) string, strlen((char*) string), 100);
	PRINT_NEW_LINE();
//	memset(string, 0, strlen((char*) string));
}
