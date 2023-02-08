/*
 * state.h
 *
 *  Created on: Feb 7, 2023
 *      Author: mswel
 */

#ifndef INC_STATE_H_
#define INC_STATE_H_



typedef struct SatelliteState* SatelliteStatePtr;

// Define all state function pointers and use typedef so
// they can be called in an easier to read way.
typedef void (*EventInitFunct) (SatelliteStatePtr);
typedef void (*EventInitialChargingFunct) (SatelliteStatePtr);
typedef void (*EventDetumblingFunct) (SatelliteStatePtr);
typedef void (*EventSafeModeFunct) (SatelliteStatePtr);
typedef void (*EventNormalOperationsFunct) (SatelliteStatePtr);

struct SatelliteState{
	EventInitFunct init;
	EventInitialChargingFunct initialCharging;
	EventDetumblingFunct detumbling;
	EventSafeModeFunct safeMode;
	EventNormalOperationsFunct normalOperations;
};

void defaultImplementation(SatelliteStatePtr state);
void transitiontoInit(SatelliteStatePtr state);
void transitiontoInitialCharging(SatelliteStatePtr state);
void transitiontoIDetumbling(SatelliteStatePtr state);
void transitiontoSafeMode(SatelliteStatePtr state);
void transitiontoNormalOperations(SatelliteStatePtr state);


#endif /* INC_STATE_H_ */
