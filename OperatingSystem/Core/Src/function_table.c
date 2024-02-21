/*
 * function_table.c
 *
 *  Created on: Feb 20, 2024
 *      Author: asjad
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "function_table.h"
#include "main.h"
#include "cmsis_os.h"

// no idea if this will work
extern UART_HandleTypeDef hlpuart1;

// define type Superior Command Entry
typedef struct {
	uint8_t cmd_byte;
	void (*cmd_func)();
} SuperiorCommandEntry;


SuperiorCommandEntry command_table[] = {

		// get data
		{0x45, system_critical_info},
		// take a picture with the camera
		{0x2A, picture},
		// orientation metrics
		{0xF0, satellite},
		// global positioning system data
		{0x69, telemetry},
		// stuff
		{0x7A, MPI_stuff},


};


void system_critical_info(){
	char * buf = "system info task\r\n";
	HAL_UART_Transmit(&hlpuart1, (uint8_t*)buf , strlen(buf), HAL_MAX_DELAY);
}

void picture(){
	char * buf = "picture task\r\n";
	HAL_UART_Transmit(&hlpuart1, (uint8_t*)buf , strlen(buf), HAL_MAX_DELAY);
}

void satellite(){
	char * buf = "satellite metrics task\r\n";
	HAL_UART_Transmit(&hlpuart1, (uint8_t*)buf , strlen(buf), HAL_MAX_DELAY);
}

void telemetry(){
	char * buf = "telemetry task\r\n";
	HAL_UART_Transmit(&hlpuart1, (uint8_t*)buf , strlen(buf), HAL_MAX_DELAY);
}

void MPI_Stuff(){
	char * buf = "MPI_stuff task\r\n";
	HAL_UART_Transmit(&hlpuart1, (uint8_t*)buf , strlen(buf), HAL_MAX_DELAY);
}
