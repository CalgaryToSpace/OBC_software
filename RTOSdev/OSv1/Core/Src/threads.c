/*
 * threads.c
 *
 *  Created on: Dec 28, 2021
 *      Author: Matthew
 */

#include "threads.h"
#include "main.h"
#include "uart.h"

extern struct threadNode* head;

//uint8_t UART1_txBuffer;
//uint8_t UART1_rxBuffer;
//UART_HandleTypeDef hlpuart1;
//UART_HandleTypeDef huart3;
//DMA_HandleTypeDef hdma_lpuart1_rx;
//SPI_HandleTypeDef hspi1;
//PCD_HandleTypeDef hpcd_USB_OTG_FS;

void mainThread(void *argument){
	int mainProcessCount = 2;
	startThread(test1, osPriorityLow, "Mem", 4*64);
	startThread(test2, osPriorityHigh, "GPS", 4*64);
	for(;;){
		vTaskDelay(pdMS_TO_TICKS(1000));
		printAllThreadInfo();
		sendUartMessage("\n", 1);
		sendUartMessage("\r", 1);
		vTaskDelay(pdMS_TO_TICKS(5000));
		killThread(findNode(osThreadGetId())->children[0]);
		if(mainProcessCount != childCount(head)){

		}
	}
}

//Test function
void test1(void *argument)
{
  for(;;)
  {
	sendUartMessage("\n", 1);
	sendUartMessage("\r", 1);
	sendUartMessage("BBBBBB", 6);
	sendUartMessage("\n", 1);
	sendUartMessage("\r", 1);
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

//Test function
void test2(void *argument)
{
	for(;;)
	{
		sendUartMessage("\n", 1);
		sendUartMessage("\r", 1);
		sendUartMessage("AAAAAA", 6);
		sendUartMessage("\n", 1);
		sendUartMessage("\r", 1);
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

void test3(void *argument){
	for(;;)
	{

	}
}
