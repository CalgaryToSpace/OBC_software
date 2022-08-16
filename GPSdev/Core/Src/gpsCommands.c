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
	char temp[Buffer];
	sprintf(temp, "%c", timeout);
	strcat(temp, command);
	sendGpsCommand(command);
	return;
}

void bdseCutoff(float angle){
	char* command = "BDSECUTOFF ";
	char temp[Buffer];
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
		strcat(" enable", command);
	}
	else if(on == 0){
		strcat(" disable", command);
	}
	else
		return;
	sendGpsCommand(command);
	return;
}

void dllTimeConst(char* signalType, float timeConst){
	char* command = "DLLTIMECONST ";
	strcar(signalType, command);
	strcat(" ", command);
	char temp[Buffer];
	sprintf(temp, sizeof(temp), "%f", timeConst);
	strcat(temp, command);
	sendGpsCommand(command);
	return;
}

void dynamics(char* settings){
	char* command = "DYNAMICS ";
	strcar(settings, command);
	sendGpsCommand(command);
	return;
}

void eCutoff(float angle){
	char* command = "ECUTOFF ";
	char temp[Buffer];
	sprintf(temp, sizeof(temp), "%f", angle);
	strcat(temp, command);
	sendGpsCommand(command);
	return;
}

void elevationCutoff(char* constellation, float angle){
	char* command = "ELEVATIONCUTOFF ";
	strcar(constellation, command);
	strcat(" ", command);
	char temp[Buffer];
	sprintf(temp, sizeof(temp), "%f", angle);
	strcat(temp, command);
	sendGpsCommand(command);
	return;
}

void fix(char* type, float param1, float param2, float param3){
	char* command = "FIX ";
	strcat(type, command);
	if(strcomp(type, "HEIGHT")){
		char temp[Buffer];
		sprintf(temp, sizeof(temp), "%f", param1);
		strcat(temp, command);
	}
	else if (strcom(type, "POSITION")){
		char temp1[Buffer];
		char temp2[Buffer];
		char temp3[Buffer];
		sprintf(temp1, sizeof(temp1), "%f", param1);
		strcat(temp1, command);
		strcat(" ", command);
		sprintf(temp2, sizeof(temp2), "%f", param2);
		strcat(temp2, command);
		strcat(" ", command);
		sprintf(temp3, sizeof(temp3), "%f", param2);
		strcat(temp3, command);
	}
	sendGpsCommand(command);
	return;
}

void freSet(char* target){
	char* command = "FRESET ";
	strcat(target, command);
	sendGpsCommand(command);
	return;
}

void geodeticDatum(char* theSwitch, char* name, float epsgCode, char* anchor, float semimajorAxis, float flattening){
	char* command = " GEODETICDATUM ";
	strcat(theSwitch, command);
	strcat(" ", command);
	strcat(name, command);
	strcat(" ", command);
	if(strcomp(theSwitch, "DELETE")){
		sendGpsCommand(command);
		return;
	}
	char temp1[Buffer];
	char temp2[Buffer];
	char temp3[Buffer];
	sprintf(temp1, sizeof(temp1), "%f", epsgCode);
	strcat(temp1, command);
	strcat(" ", command);
	strcat(anchor, command);
	sprintf(temp2, sizeof(temp1), "%f", semimajorAxis);
	strcat(temp2, command);
	strcat(" ", command);
	sprintf(temp3, sizeof(temp3), "%f", flattening);
	strcat(temp3, command);
	sendGpsCommand(command);
	return;
}

void itDetectConfig(char* rfPath){
	char* command = "ITDETECTCONFIG ";
	strcat(rfPath, command);
	sendGpsCommand(command);
	return;
}

void log(char* port, char* message, char* trigger, float period, float offset, char* hold){
	char* command = "LOG ";
	char temp1[Buffer];
	char temp2[Buffer];
	strcat(port, command);
	strcat(" ", command);
	strcat(message, command);
	strcat(" ", command);
	strcat(trigger, command);
	strcat(" ", command);
	sprintf(temp1, sizeof(temp1), "%f", period);
	sprintf(temp2, sizeof(temp1), "%f", offset);
	strcat(temp1, command);
	strcat(" ", command);
	strcat(temp2, command);
	strcat(" ", command);
	strcat(hold, command);
	sendGpsCommand(command);
	return;
}

void posTimeOut(float seconds){
	char* command = "POSTIMEOUT ";
	char temp[Buffer];
	sprintf(temp, sizeof(temp), "%f", seconds);
	strcat(temp, command);
	sendGpsCommand(command);
	return;
}

void ppsControl(char* theSwitch, char* polarity, float period, float pulseWidth){
	char* command = "PPSCONTROL ";
	char temp1[Buffer];
	char temp2[Buffer];
	strcat(theSwitch, command);
	strcat(" ", command);
	strcat(polarity, command);
	strcat(" ", command);
	sprintf(temp1, sizeof(temp1), "%f", period);
	sprintf(temp2, sizeof(temp2), "%f", pulseWidth);
	strcat(temp1, command);
	strcat(" ", command);
	strcat(temp2, command);
	sendGpsCommand(command);
	return;
}

void reset(float delay){
	char* command = "RESET ";
	char temp[Buffer];
	sprintf(temp, sizeof(temp), "%f", delay);
	strcat(temp, command);
	sendGpsCommand(command);
	return;
}

void saveConfig(){
	char* command = " SAVECONFIG";
	sendGpsCommand(command);
	return;
}

void serialProtocol(char* port, char* protocol){
	char* command = " SERIALPROTOCOL ";
	strcat(port, command);
	strcat(" ", command);
	strcat(protocol, command);
	sendGpsCommand(command);
	return;
}

void setApproxPos(float lat, float lon, float height){
	char* command = "SETAPPROXPOS ";
	char temp1[Buffer];
	char temp2[Buffer];
	char temp3[Buffer];
	sprintf(temp1, sizeof(temp1), "%f", lat);
	sprintf(temp2, sizeof(temp2), "%f", lon);
	sprintf(temp3, sizeof(temp3), "%f", height);
	strcat(temp1, command);
	strcat(" ", command);
	strcat(temp2, command);
	strcat(" ", command);
	strcat(temp3, command);
	sendGpsCommand(command);
	return;
}

void setApproxTime(float week, float second){
	char* command = "SETAPPROXTIME ";
	char temp1[Buffer];
	char temp2[Buffer];
	sprintf(temp1, sizeof(temp1), "%f", week);
	sprintf(temp2, sizeof(temp2), "%f", second);
	strcat(temp1, command);
	strcat(" ", command);
	strcat(temp2, command);
	sendGpsCommand(command);
	return;
}

void setionoType(char* model){
	char* command = " SETIONOTYPE ";
	strcat(model, command);
	sendGpsCommand(command);
	return;
}

void statusConfig(char* type, char* word, float mask){
	char* command = "STATUSCONFIG ";
	char temp[Buffer];
	strcat(type, command);
	strcat(" ", command);
	strcat(word, command);
	strcat(" ", command);
	sprintf(temp, sizeof(temp), "%f", mask);
	strcat(mask, command);
	sendGpsCommand(command);
	return;
}

void tiltCompensationControl(char* theSwitch){
	char* command = "TILTCOMPENSATIONCONTROL ";
	strcat(theSwitch, command);
	sendGpsCommand(command);
	return;
}
