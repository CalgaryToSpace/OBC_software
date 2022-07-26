/*
 * gpsCommands.h
 *
 *  Created on: Jul 25, 2022
 *      Author: mswel
 */

#ifndef INC_GPSCOMMANDS_H_
#define INC_GPSCOMMANDS_H_

void antennaPower(int on);

void approxPosTimeout(int timeout);

void bdseCutoff(float angle);

void bestVelType(char* mode);

void dataDecodeSignal(char* signalType, int on);

dllTimeConst();

dynamics();

eCutoff();

elevationCutoff();

fix();

freSet();

geodeticDatum();

itDetectConfig();

log();

posTimeOut();

ppsControl();

reset();

saveConfig();

serialProtocol();

setApproxPos();

setApproxTime();

setionoType();

statusConfig();

tiltCompensationontrol();



#endif /* INC_GPSCOMMANDS_H_ */
