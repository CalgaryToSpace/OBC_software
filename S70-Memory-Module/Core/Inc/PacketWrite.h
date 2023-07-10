/*
 * PakcetWrite.h
 *
 *  Created on: Jul. 4, 2023
 *      Author: Saksham Puri
 */

#ifndef INC_PACKETWRITE_H_
#define INC_PACKETWRITE_H_

#include "MemoryUtilities.h"

uint8_t WRITE(SPI_HandleTypeDef hspi1, void * packetBuffer);

#endif /* INC_PACKETWRITE_H_ */
