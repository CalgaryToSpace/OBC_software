#include <stdio.h>

typedef enum { 
    st_init,
    st_charging,
    st_detumbling,
    st_safeMode,
    st_state,
    //insert any new states above state count
    STATE_COUNT
} state;

typedef struct {
    state currState;
} stateMachine_t;

typedef enum { //need to change telecommand to something usable
    telecommand,       
    sufficientBattery,
    telecommandDetumble,
    lowBattery,
    criticalError,
    detumbled,
    //insert any new states above event count
    EVENT_COUNT
} event; //issue need to figure out how to make it so multiple events can possibly lead to the same event

typedef struct { //pre establishes the properties of a state function
    void(*func)(void);
} stateFunction;

typedef struct {
    event arrow[EVENT_COUNT];
    state correspond[EVENT_COUNT];
} transitions;



void initFunc () {
    printf("Init\n");
}

void chargingFunc(){
    printf("Initial Charging\n");
}

void detumblingFunc(){
    printf("Detumbling\n");
}

void safeModeFunc(){
    printf("Safe Mode\n");
}

void stateFunc(){
    printf("Normal Operations\n");
}

state stubFunc(event action) {
    return st_state;
}


typedef struct {    //structure defining the properties of the state
    state current_st; //state being defined
    transitions matrix;
     void (*stateFunc)(void);
} stateProperties; //if there are multiple states that can be transitioned into keep it such that 

static stateProperties transitionTable[STATE_COUNT] ={
    {st_init, 
        {{telecommand,sufficientBattery, telecommandDetumble, lowBattery, criticalError, detumbled}, 
            {st_init, st_init, st_charging, st_init, st_init, st_init}}, initFunc},
    {st_charging, 
        {{telecommand,sufficientBattery, telecommandDetumble, lowBattery, criticalError, detumbled}, 
            {st_charging, st_detumbling,st_charging,st_charging,st_charging,st_charging}}, chargingFunc},
    {st_detumbling,
         {{telecommand,sufficientBattery, telecommandDetumble, lowBattery, criticalError, detumbled}, 
            {st_detumbling,st_detumbling,st_detumbling,st_charging,st_detumbling,st_safeMode}}, detumblingFunc},
    {st_safeMode,
         {{telecommand,sufficientBattery, telecommandDetumble, lowBattery, criticalError, detumbled},
             {st_state,st_safeMode,st_safeMode,st_safeMode,st_safeMode,st_safeMode}}, safeModeFunc},
    {st_state,
         {{telecommand,sufficientBattery, telecommandDetumble, lowBattery, criticalError, detumbled}, 
            {st_state,st_state,st_state,st_safeMode,st_safeMode,st_state}}, stateFunc},
};


/*
event transition[STATE_COUNT] = {st_init,
    st_charging,
    st_detumbling,
    st_safeMode,
    st_state};
*/

event parser (){ //temporary method to convert input into event 
    int cmd;
    printf("\nEnter an integer: ");
    scanf("%d", &cmd);
    switch (cmd) {
        case 0:
            return telecommand;
        case 1:
            return sufficientBattery;
        case 2:
            return telecommandDetumble;
        case 3:
            return lowBattery;
        case 4:
            return criticalError;
        case 5:
            return detumbled;
        //need to add error handling
    }
}


void StateMachine_RunIteration(stateMachine_t *stateMachine, event trigger){  
    //changes the actual state
    stateMachine->currState = transitionTable[stateMachine->currState].matrix.correspond[trigger];
    transitionTable[stateMachine->currState].stateFunc();
}

int main(){
    stateMachine_t machine;
    machine.currState = st_init;
    //intialization iteration run
    StateMachine_RunIteration(&machine, 0); 
    while(1){
        printf("State is: %d \n",machine.currState);
        StateMachine_RunIteration(&machine, parser()); 
    }
    
}