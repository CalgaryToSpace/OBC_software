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
	startThread(test1, osPriorityLow, "One", 8*64);
	for(;;){
		//vTaskDelay(pdMS_TO_TICKS(1000));
//		sendUartMessage("zro", 3);
//		printAllThreadInfo();
//		sendUartMessage("\n", 1);
//		sendUartMessage("\r", 1);
		vTaskDelay(pdMS_TO_TICKS(50));
//		killThread(findNode(osThreadGetId())->children[0]);
//		if(mainProcessCount != childCount(head)){
//
//		}
	}
}

//Test function
void test1(void *argument)
{
  startThread(test2, osPriorityLow, "Two", 8*64);
  //vTaskDelay(pdMS_TO_TICKS(2000));
  sendUartMessage("Uno", 3);
  printAllThreadInfo();
  sendUartMessage("\n", 1);
  sendUartMessage("\r", 1);
  for(;;)
  {
//	sendUartMessage("\n", 1);
//	sendUartMessage("\r", 1);
//	sendUartMessage("111111", 6);
//	sendUartMessage("\n", 1);
//	sendUartMessage("\r", 1);
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

//Test function
void test2(void *argument)
{
	//startThread(test3, osPriorityHigh, "fre", 4*64);
	vTaskDelay(pdMS_TO_TICKS(500));
	sendUartMessage("duo", 3);
	printAllThreadInfo();
//	sendUartMessage("\n", 1);
//	sendUartMessage("\r", 1);
	for(;;)
	{
//		sendUartMessage("\n", 1);
//		sendUartMessage("\r", 1);
//		sendUartMessage("222222", 6);
//		sendUartMessage("\n", 1);
//		sendUartMessage("\r", 1);
		vTaskDelay(pdMS_TO_TICKS(500));
	}
}

void test3(void *argument){
	vTaskDelay(pdMS_TO_TICKS(1000));
	printAllThreadInfo();
	sendUartMessage("\n", 1);
	sendUartMessage("\r", 1);
	for(;;)
	{

	}
}
