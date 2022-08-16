/*
 * gpsCommands.h
 *
 *  Created on: Jul 25, 2022
 *      Author: mswel
 */

#ifndef INC_GPSCOMMANDS_H_
#define INC_GPSCOMMANDS_H_

enum bufferSize{
	Buffer = 32,
};

void antennaPower(int on);

void approxPosTimeout(int timeout);

void bdseCutoff(float angle);

void bestVelType(char* mode);

void dataDecodeSignal(char* signalType, int on);

void dllTimeConst(char* signalType, float timeConst);

void dynamics(char* settings);

void eCutoff(float angle);

void elevationCutoff(char* constellation, float angle);

void fix(char* type, float param1, float param2, float param3);

void freSet(char* target);

void geodeticDatum(char* theSwitch, char* name, float epsgCode, char* anchor, float semimajorAxis, float flattening);

void itDetectConfig(char* rfPath);

void log(char* port, char* message, char* trigger, float period, float offset, char* hold);

void posTimeOut(float seconds);

void ppsControl(char* theSwitch, char* polarity, float period, float pulseWidth);

void reset(float delay);

void saveConfig();

void serialProtocol(char* port, char* protocol);

void setApproxPos(float lat, float lon, float height);

void setApproxTime(float week, float second);

void setionoType(char* model);

void statusConfig(char* type, char* word, float mask);

void tiltCompensationControl(char* theSwitch);



#endif /* INC_GPSCOMMANDS_H_ */
