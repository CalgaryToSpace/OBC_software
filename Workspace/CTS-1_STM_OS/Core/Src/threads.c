/*
 * threads.c
 *
 *  Created on: Dec 28, 2021
 *      Author: Matthew
 */

#include "threads.h"
#include "main.h"
#include "uart.h"

//uint8_t UART1_txBuffer;
//uint8_t UART1_rxBuffer;
//UART_HandleTypeDef hlpuart1;
//UART_HandleTypeDef huart3;
//DMA_HandleTypeDef hdma_lpuart1_rx;
//SPI_HandleTypeDef hspi1;
//PCD_HandleTypeDef hpcd_USB_OTG_FS;


//Test function
void StartTest1(void *argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
	  sendUartMessage("\n", 1);
	  sendUartMessage("\r", 1);
	  sendUartMessage("Test 1", 6);
	  sendUartMessage("\n", 1);
	  sendUartMessage("\r", 1);
//	HAL_UART_Transmit(&hlpuart1, (uint8_t*)"\n", 1, HAL_MAX_DELAY);
//	HAL_UART_Transmit(&hlpuart1, (uint8_t*)"\r", 1, HAL_MAX_DELAY);
//	HAL_UART_Transmit(&hlpuart1, (uint8_t*)"Test 1", 26, HAL_MAX_DELAY);
//	HAL_UART_Transmit(&hlpuart1, (uint8_t*)"\n", 1, HAL_MAX_DELAY);
//	HAL_UART_Transmit(&hlpuart1, (uint8_t*)"\r", 1, HAL_MAX_DELAY);
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
  /* USER CODE END 5 */
}

//Test function
void StartTest2(void *argument)
{
  /* USER CODE BEGIN StartTask02 */
  /* Infinite loop */
	for(;;)
	{
		sendUartMessage("\n", 1);
		sendUartMessage("\r", 1);
		sendUartMessage("Test 2", 6);
		sendUartMessage("\n", 1);
		sendUartMessage("\r", 1);
//		HAL_UART_Transmit(&hlpuart1, (uint8_t*)"\n", 1, HAL_MAX_DELAY);
//		HAL_UART_Transmit(&hlpuart1, (uint8_t*)"\r", 1, HAL_MAX_DELAY);
//		HAL_UART_Transmit(&hlpuart1, (uint8_t*)"Test 2", 26, HAL_MAX_DELAY);
//		HAL_UART_Transmit(&hlpuart1, (uint8_t*)"\n", 1, HAL_MAX_DELAY);
//		HAL_UART_Transmit(&hlpuart1, (uint8_t*)"\r", 1, HAL_MAX_DELAY);
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
  /* USER CODE END StartTask02 */
}
