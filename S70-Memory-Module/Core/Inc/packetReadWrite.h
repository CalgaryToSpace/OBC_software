/*
 * packetReadWrite.h
 *
 *  Created on: Jul. 20, 2023
 *      Author: Saksham Puri
 */

#ifndef INC_PACKETREADWRITE_H_
#define INC_PACKETREADWRITE_H_

#include "MemoryUtilities.h"

void INITIALIZE();
uint8_t WRITE(SPI_HandleTypeDef *hspi1, uint8_t * packetBuffer);
uint8_t WRITE_LFS(SPI_HandleTypeDef *hspi1, uint8_t * packetBuffer, lfs_block_t block, lfs_size_t size);
uint8_t READ(SPI_HandleTypeDef *hspi1, uint8_t * spiRxBuffer);
uint8_t READ_LFS(SPI_HandleTypeDef *hspi1, uint8_t * spiRxBuffer, lfs_block_t block, lfs_size_t size);

#endif /* INC_PACKETREADWRITE_H_ */
