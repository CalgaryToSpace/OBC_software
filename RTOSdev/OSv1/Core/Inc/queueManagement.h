/*
 * queueManagement.h
 *
 *      Author: Sahithi
 */

#ifndef INC_QUEUEMANAGEMENT_H_
#define INC_QUEUEMANAGEMENT_H_

#include <stdio.h>
#include <stdint.h>
#include "FreeRTOS.h"
#include "queue.h"

typedef enum {

	MAIN = 0,
	RXTX = 1,
	MANC = 2,
	LOGT = 3,
	ACDS = 4,
	MPIT = 5,
	GPST = 6

} DataCode_t;

typedef struct {

	uint8_t ucValue;
	DataCode_t eDataSource;
	DataCode_t eDataDest;
	char* context;

} DataSend_t;


void vSenderTask(void *arg);

void startMessengeCoordinator(QueueHandle_t messenger_handle);

QueueHandle_t* createMessegeQueues();

#endif /* INC_QUEUEMANAGEMENT_H_ */
