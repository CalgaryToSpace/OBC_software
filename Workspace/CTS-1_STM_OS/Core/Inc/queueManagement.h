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

	MPI,
	Camera,
	GPS

} DataSource_t;

typedef struct {

	uint8_t ucValue;
	DataSource_t eDataSource;

} Data_t;

typedef struct {

	QueueHandle_t queueHandle;
	Data_t dataToSendPtr;

} DataSend_t;

static const Data_t xStructsToSend[3] = {
	{1, MPI},
	{2, Camera},
	{3, GPS}
};

void vSenderTask(void *arg);
void vReceiverTask(void *arg);

#endif /* INC_QUEUEMANAGEMENT_H_ */
