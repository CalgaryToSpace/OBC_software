/*
 * queueManagement.c
 *
 *      Author: Sahithi
 */

#include "main.h"
#include "queueManagement.h"
#include "uart.h"

UART_HandleTypeDef hlpuart1;

void vSenderTask(void *arg) {

	DataSend_t *arg_struc = (DataSend_t *) arg;
	QueueHandle_t qHandle = arg_struc->queueHandle;
	Data_t dataToSend = arg_struc->dataToSendPtr;
	BaseType_t sendStatus;


	for(;;) {

		sendStatus = xQueueSendToBack(qHandle, &dataToSend, 0);

		if(sendStatus != pdPASS) {
			sendUartMessage("Could not send to the queue.", 28);
			sendUartMessage("\n", 1);
			sendUartMessage("\r", 1);
		}
	}

}

void vReceiverTask(void *arg) {

	QueueHandle_t qHandle = arg;
	Data_t xReceivedStructure;
	BaseType_t readStatus;
	const TickType_t xTicksToWait = pdMS_TO_TICKS(100);

	for(;;) {

		if(uxQueueMessagesWaiting(qHandle) != 0) {
			sendUartMessage("Queue should have been empty.", 29);
			sendUartMessage("\n", 1);
			sendUartMessage("\r", 1);
		}

		readStatus = xQueueReceive(qHandle, &xReceivedStructure, xTicksToWait);

		if(readStatus == pdPASS) {
			switch(xReceivedStructure.eDataSource) {

				case MPI :
					sendUartMessage("From MPI = ", 11);
					HAL_UART_Transmit(&hlpuart1, (uint8_t*)&xReceivedStructure.ucValue, 1, HAL_MAX_DELAY);
					sendUartMessage("\n", 1);
					sendUartMessage("\r", 1);
					break;

				case Camera :
					sendUartMessage("From Camera = ", 14);
					HAL_UART_Transmit(&hlpuart1, (uint8_t*)&xReceivedStructure.ucValue, 1, HAL_MAX_DELAY);
					sendUartMessage("\n", 1);
					sendUartMessage("\r", 1);
					break;

				case GPS :
					sendUartMessage("From GPS = ", 11);
					HAL_UART_Transmit(&hlpuart1, (uint8_t*)&xReceivedStructure.ucValue, 1, HAL_MAX_DELAY);
					sendUartMessage("\n", 1);
					sendUartMessage("\r", 1);
					break;
			}
		} else {

			sendUartMessage("Could not receive from the queue.", 33);
			sendUartMessage("\n", 1);
			sendUartMessage("\r", 1);

		}
	}

}
