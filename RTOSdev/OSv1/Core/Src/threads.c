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
	QueueHandle_t coordinatorQueue = xQueueCreate(7, sizeof(uint8_t) * 100);
	startThread(startMessengeCoordinatorTask, osPriorityLow, "One", 8*64, (void*)coordinatorQueue);
	for(;;){

	}
}
