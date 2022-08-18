#ifndef SENSORFSM_H_
#define SENSORFSM_H_

#include "PortPins.h"
#include "Switch.h"
#include "FSMSwitchDebounce.h"

// Type Definitions
typedef enum {
    Normal_Operation, Take_It_Slow, Stop, SensorWait
} FSMState1;

typedef struct {
    FSMState1 CurrentState;      // Current state of the FSM
    SwitchStatus CurrentInput;  // Current input of the FSM
} FSMTypeSensor;

// Function Prototypes
void InitializeSensorFSM(FSMTypeSensor *FSM);
FSMState1 NextSensorStateFunction(FSMTypeSensor *FSM);
void OutputSensorFunction(FSMTypeSensor *FSM);

#endif /* FSM_H_ */
