/*
 * PacketRead.h
 *
 *  Created on: Jul. 10, 2023
 *      Author: Saksham Puri
 */

#ifndef INC_PACKETREAD_H_
#define INC_PACKETREAD_H_

#include "MemoryUtilities.h"

uint8_t READ(SPI_HandleTypeDef *hspi1, uint8_t * spiRxBuffer);

#endif /* INC_PACKETREAD_H_ */
