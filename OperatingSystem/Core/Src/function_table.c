/*
 * function_table.c
 *
 *  Created on: Feb 20, 2024
 *      Author: asjad
 */


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
