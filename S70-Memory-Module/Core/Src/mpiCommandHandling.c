/*
 * mpiCommandHandling.c
 *
 * Author: Vaibhav Kapoor
 */

#include <../Inc/mpiCommandHandling.h>
#include <../Inc/DebugUtilities.h>
#include "string.h"
#include <stdio.h>
#include "main.h"
#include "packetReadWrite.h"
#include "DebugUtilities.h"

#define BUFFER_SIZE 160

// This function sends commands to the MPI. Parameters argument is set to NULL when no parameters are required as part of a command.
// TODO: Add error check
uint8_t sendTelecommand(uint8_t commandCode, uint8_t parameters){

	// Buffers for storing incoming and outgoing frames
	uint8_t UART1_txBuffer[BUFFER_SIZE] = {0};
	uint8_t UART1_rxBuffer[BUFFER_SIZE] = {0};

	// Turn on frame transmitting TC
	UART1_txBuffer[0] = 0x54;
	UART1_txBuffer[1] = 0x43;
	UART1_txBuffer[2] = commandCode;

	// Command with no parameters detected: Transmit command
	if(parameters != 0xFF){
		UART1_txBuffer[3] = parameters;
	}

	// Transmit command
	HAL_UART_Transmit(&huart1, (uint8_t *)UART1_txBuffer, strlen((char*)UART1_txBuffer), 100);
	HAL_UART_Receive_DMA(&huart1, UART1_rxBuffer, BUFFER_SIZE);

	return 1;
}

// This function reads incoming data frames such as science data and processes it to display useful information
uint8_t parseIncomingMPIFrames(){

	// Buffer stores incoming data frame
	uint8_t buffer[BUFFER_SIZE];
	MpiFrame_t frame;

	// Continuously read incoming data frames
	while(1){
		HAL_UART_Receive_DMA(&huart1, buffer, BUFFER_SIZE);

		// Copy frame data from the buffer into a formatted Struct
		frame.sync_byte1 = buffer[0];
		frame.sync_byte2 = buffer[1];
		frame.sync_byte3 = buffer[2];
		frame.sync_byte4 = buffer[3];
		frame.frame_counter = (buffer[4] << 8) + buffer[5]; // (buffer[4] << 8) is the same as (buffer[4] * 256)
		frame.board_temperature = (buffer[6] << 8) + buffer[7];
		frame.firmware_version = buffer[8];
		frame.mpi_unit_id = buffer[9];
		frame.detector_status = (buffer[10] << 8) + buffer[11];
		frame.inner_dome_voltage_setting = (buffer[12] << 8) + buffer[13];
		frame.spib_reserved = buffer[14];
		frame.inner_dome_scan_index = buffer[15];
		frame.faceplate_voltage_setting = (buffer[16] << 8) + buffer[17];
		frame.faceplate_voltage_adc_reading = (buffer[18] << 8) + buffer[19];
		frame.inner_dome_voltage_adc_reading = (buffer[20] << 8) + buffer[21];

		// Copy the pixel array (assuming 67 elements)
		for (int i = 0; i < 67; ++i) {
		    frame.pixels[i] = (buffer[22 + i * 2] << 8) + buffer[23 + i * 2];
		}

		// Copy the cyclic redundancy check (CRC)
		frame.cyclic_redundancy_check = (buffer[156] << 8) + buffer[157];


		// TODO: Error Check Data Frame & handle buffer overloading

		// Process frame data to display/test
		processFrameData(frame);
	}

	// Success Event
	return 1;
}

// Test function to parse relevant info from data frames
void processFrameData(MpiFrame_t frame){

	// Define an array of buffers for each variable in the structure that needs to be tested
	char variable_buffer[255];

	// Clear the buffer before use
	variable_buffer[0] = '\0';

	// Concatenate test variable values into the char buffer to send formatted values over
	sprintf(
			variable_buffer,
			"Frame Counter: %u, Board Temperature: %u, Voltage ADC Reading: %u\n",
			frame.frame_counter,
			frame.board_temperature,
			frame.faceplate_voltage_adc_reading
	);

	// Send formatted data over HLPUART for verification
	//HAL_UART_Transmit(&hlpuart1, (uint8_t*)variable_buffer, strlen(variable_buffer), HAL_MAX_DELAY);
	PRINT_STRING_UART(variable_buffer);

	//TODO: For testing write parsed and raw data to files to verify and update test plans
	writeFrameToMemory(frame);

}

// This function deals with writing data packets to memory using MEMORY UTILITIES
void writeFrameToMemory(MpiFrame_t frame){

	//Calling the WRITE function and making sure it's successful
	if (WRITE(&hspi1, (uint8_t*) &frame) == 0) {
		PRINT_STRING_UART("Frame Written successfully");
	} else {
		PRINT_STRING_UART("Error Occurred while writing frame");
	}
}






