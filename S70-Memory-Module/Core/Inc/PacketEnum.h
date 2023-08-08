/*
 * PacketEnum.h
 *
 *  Created on: Jul. 3, 2023
 *      Author: Saksham Puri
 */

#ifndef INC_PACKETENUM_H_
#define INC_PACKETENUM_H_

typedef enum {Telemetry, ADCS, PowerSystems} packet_type;

typedef struct telemetry {
	packet_type type;
	int secondsSinceBoot;
	double temperature;
} tel;

typedef struct MPI_Data {
	packet_type type;
	char data[100];
	int time_collected;
} MPI;

#endif /* INC_PACKETENUM_H_ */
