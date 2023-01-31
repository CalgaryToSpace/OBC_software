/*
 * queueManagement.c
 *
 *      Author: Sahithi
 */

#include "main.h"
#include "queueManagement.h"
#include "uart.h"
#include "queue.h"

UART_HandleTypeDef hlpuart1;

void startMessengeCoordinatorTask(void *messenger_handle){
	QueueHandle_t *qHandle = (QueueHandle_t *)messenger_handle;
	DataSend_t xReceivedStructure;
	BaseType_t readStatus;
	BaseType_t sendStatus;
	QueueHandle_t* addresses = createMessageQueues();
	const TickType_t xTicksToWait = pdMS_TO_TICKS(0);

	for(;;) {

		// Sahithi had this and I don't know why -Matt
		//if(uxQueueMessagesWaiting(qHandle) != 0) {
			// Logging here eventually: "Queue should have been empty."
		//}

		readStatus = xQueueReceive(qHandle, &xReceivedStructure, xTicksToWait);

		if(readStatus == pdPASS) {
			switch(xReceivedStructure.eDataSource) {

				case "MAIN" :
					sendStatus = xQueueSendToBack(addresses[MAIN], &dataToSend, 0);
					break;

				case "RXTX" :
					sendStatus = xQueueSendToBack(addresses[RXTX], &dataToSend, 0);
					break;

				case "MANC" :
					sendStatus = xQueueSendToBack(addresses[MANC], &dataToSend, 0);
					break;

				case "LOGT" :
					sendStatus = xQueueSendToBack(addresses[LOGT], &dataToSend, 0);
					break;

				case "ACDS" :
					sendStatus = xQueueSendToBack(addresses[ACDS], &dataToSend, 0);
					break;

				case "MPIT" :
					sendStatus = xQueueSendToBack(addresses[MPIT], &dataToSend, 0);
					break;

				case "GPST" :
					sendStatus = xQueueSendToBack(addresses[GPST], &dataToSend, 0);
					break;
			}
			if(sendStatus != pdPASS){

				// PUT SOMETHING FOR LOGGING HERE EVENTUALLY

			}
		} else {

			// POSSIBLY PUT SOMETHING HERE FOR LOGGING, BUT PROBABLY NOT NECESSARY

		}
	}
}

QueueHandle_t* createMessegeQueues(){
	QueueHandle_t the_addresses[7];
	the_addresses[MAIN] = xQueueCreate(7, sizeof(uint8_t) * 100);
	the_addresses[RXTX] = xQueueCreate(7, sizeof(uint8_t) * 100);
	the_addresses[MANC] = xQueueCreate(7, sizeof(uint8_t) * 100);
	the_addresses[LOGT] = xQueueCreate(7, sizeof(uint8_t) * 100);
	the_addresses[ACDS] = xQueueCreate(7, sizeof(uint8_t) * 100);
	the_addresses[MPIT] = xQueueCreate(7, sizeof(uint8_t) * 100);
	the_addresses[GPST] = xQueueCreate(7, sizeof(uint8_t) * 100);
	return the_addresses;
}


	int passMessage(){
}


