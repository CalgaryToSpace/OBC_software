/*
 * gpsCommands.c
 *
 *  Created on: Jul 25, 2022
 *      Author: mswel
 */

#include "gpsCommands.h"
#include "send.h"
#include <string.h>

void antennaPower(int on){
	char* command = "ANTENNAPOWER ";
	if(on == 1){
		strcat("ON", command);
	}
	else if(on == 0){
		strcat("OFF", command);
	}
	else
		return;
	sendGpsCommand(command);
	return;
}

void approxPosTimeout(int timeout){
	char* command = "APPROXPOSTIMEOUT ";
	char temp[10];
	sprintf(temp, "%c", timeout);
	strcat(temp, command);
	sendGpsCommand(command);
	return;
}

void bdseCutoff(float angle){
	char* command = "BDSECUTOFF ";
	char temp[64];
	sprintf(temp, sizeof(temp), "%f", angle);
	strcat(temp, command);
	sendGpsCommand(command);
	return;
}

void bestVelType(char* mode){
	char* command = "BESTVELTYPE ";
	strcat(mode, command);
	sendGpsCommand(command);
	return;
}

void dataDecodeSignal(char* signalType, int on){
	char* command = "DATADECODESIGNAL ";
	strcat(signalType, command);
	if(on == 1){
		strcat(" enable");
	}
	else if(on == 0){
		strcat(" disable");
	}
	else
		return;
	sendGpsCommand(command);
	return;
}
