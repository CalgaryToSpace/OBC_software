/*
 * mpiCommands.h
 *
 *  Created on: Nov 17, 2023
 *      Author: vaibh
 */

#ifndef INC_MPICOMMANDHANDLING_H_
#define INC_MPICOMMANDHANDLING_H_
#include "main.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>

// This Struct lays out a MPI data frame that consists of four synchronization bytes, a two-byte frame counter, housekeeping telemetry, image pixel data, and a two-byte CRC
typedef struct {
	uint8_t sync_byte1;
	uint8_t sync_byte2;
	uint8_t sync_byte3;
	uint8_t sync_byte4;
	uint16_t frame_counter;
	int16_t board_temperature;
	uint8_t firmware_version;
	uint8_t mpi_unit_id;
	uint16_t detector_status;
	uint16_t inner_dome_voltage_setting;
	uint8_t spib_reserved;
	uint8_t inner_dome_scan_index;
	uint16_t faceplate_voltage_setting;
	uint16_t faceplate_voltage_adc_reading;
	uint16_t inner_dome_voltage_adc_reading;
	uint16_t pixels[67];
	uint16_t cyclic_redundancy_check;
} MpiFrame_t;

uint8_t sendTelecommand(uint8_t commandCode, uint8_t parameters);
uint8_t parseIncomingMPIFrames();
void processFrameData(MpiFrame_t frame);


#endif /* INC_MPICOMMANDHANDLING_H_ */
