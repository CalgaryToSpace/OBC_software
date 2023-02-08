/*
 * state.c
 *
 *  Created on: Feb 7, 2023
 *      Author: mswel
 */

#include "state.h"

static void defaultInit(SatelliteStatePtr state){
}

static void defaultInitialCharging(SatelliteStatePtr state){
}

static void defaultDetumbling(SatelliteStatePtr state){
}

static void defaultSafeMode(SatelliteStatePtr state){
}

static void defaultNormalOperations(SatelliteStatePtr state){
}

static void initState(SatelliteStatePtr state){
	transitionToInit(state);
}

static void initialChargingState(SatelliteStatePtr state){
	transitionToInitialCharging(state);
}

static void detumblingState(SatelliteStatePtr state){
	transitionToDetumbling(state);
}

static void safeModeState(SatelliteStatePtr state){
	transitionToSafeMode(state);
}

static void normalOperationsState(SatelliteStatePtr state){
	transitionToNormalOperation(state);
}



void defaultImplementation(SatelliteStatePtr state){
	state->init = defaultInit;
	state->initialCharging = defaultInitialCharging;
	state->detumbling = defaultDetumbling;
	state->safeMode = defaultSafeMode;
	state->normalOperations = defaultNormalOperations;
}

void transitiontoInit(SatelliteStatePtr state){
	defaultImplementation(state);
	state->initialCharging = initialChargingState;
}
void transitiontoInitialCharging(SatelliteStatePtr state){
	defaultImplementation(state);
	state->detumbling = detumblingState;
}
void transitiontoIDetumbling(SatelliteStatePtr state){
	defaultImplementation(state);
	state->initialCharging = initialChargingState;
	state->safeMode = safeModeState;
}
void transitiontoSafeMode(SatelliteStatePtr state){
	defaultImplementation(state);
	state->normalOperations = normalOperationsState;
}
void transitiontoNormalOperations(SatelliteStatePtr state){
	defaultImplementation(state);
	state->safeMode = safeModeState;
}

