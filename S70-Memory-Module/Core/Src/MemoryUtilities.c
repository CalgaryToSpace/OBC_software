/*
 * MemoryUtilities.c
 *
 *  Created on: Jul. 4, 2023
 *      Author: Saksham Puri
 */

#include "MemoryUtilities.h"
#include "DebugUtilities.h"
/*
 * Chip Select set to LOW
 */
void PULL_CS() {
	// same as memory_bank_counter % 8
//	uint8_t mem_bank = (memory_bank_counter & 0x7);
//	uint8_t lsb = mem_bank & 0x1;
//	uint8_t middle_bit = mem_bank & 0x2;
//	uint8_t msb = mem_bank & 0x4;
//
//	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET); // LSB
//	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_1, GPIO_PIN_RESET); // Middle Input
//	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_0, GPIO_PIN_RESET); // MSB

	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET); // LSB

}

/*
 * Chip Select set to HIGH
 * This is the default state of the CS
 */
void SET_CS() {
	// Below is A0
//	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET);
	// A1
//	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_1, GPIO_PIN_SET);
	// A2
//	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_0, GPIO_PIN_SET);

	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET);
}

/*
 * @param Takes any type of array/pointer, always converts to uint8_t pointer
 * @return Nothing, Reads Status Register, stores value in param
 * Sets Decoder Inputs BeforeHand
 * Pull All Decoder Inputs High After
 *
 */
void READ_STATUS_REGISTER(SPI_HandleTypeDef *hspi1, uint8_t *rxBuf) {
	PULL_CS();
	HAL_SPI_Transmit(hspi1, (uint8_t*) &FLASH_STATREG1, 1, 100);
	HAL_SPI_Receive(hspi1, (uint8_t*) rxBuf, 1, 100);
	SET_CS();
}

/*
 * Just Transmit WREN Command
 * Sets Decoder Inputs beforehand
 * Pull all Decoder Inputs High After
 */
void ENABLE_WREN(SPI_HandleTypeDef *hspi1) {
	PULL_CS();
	HAL_SPI_Transmit(hspi1, (uint8_t*) &FLASH_WREN, 1, 100);
	SET_CS();
}

/*
 * Just Transmit WRDI Command
 * As noted  in Section 9.3.9 of the Manual,
 * ALL Chip Selects must be pulled high in order for this command
 * to go through
 */
void ENABLE_WRDI(SPI_HandleTypeDef *hspi1) {
	SET_CS();
	HAL_SPI_Transmit(hspi1, (uint8_t*) &FLASH_WRDI, 1, 100);
}

/*
 * @param Takes a void pointer which is converted to uint8_t used as an address
 * The function takes an address and clears the memory in that address
 * We wait until the clearing is done and then end the function
 */
void MEM_CLEAR(SPI_HandleTypeDef *hspi1, uint8_t * addr) {
	ENABLE_WREN(hspi1);

	uint8_t **ptr = &addr;

	PULL_CS();
	HAL_SPI_Transmit(hspi1, (uint8_t*)&FLASH_SECTOR_ERASE, 1, 100);
	HAL_SPI_Transmit(hspi1, (uint8_t*)*ptr, 3, 100);
	SET_CS();

	uint8_t wip = 1;
	while (wip) {
		uint8_t buf[10];
		READ_STATUS_REGISTER(hspi1, buf);
		wip = 1 & buf[0];
	}
}
