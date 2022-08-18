#ifndef FSM_H_
#define FSM_H_

#include "PortPins.h"
#include "Switch.h"
#include "FSMSwitchDebounce.h"

// Type Definitions
typedef enum {
    //BothLEDsOff, RedOffGreenOn, RedOnGreenOff, BothLEDsOn
    Left, Right, Center, Stop_Bump, Lost, Wait, SharpRight, SharpLeft, Choose, Finish
} FSMState;

typedef struct {
    FSMState CurrentState;      // Current state of the FSM
    SwitchStatus CurrentInput;  // Current input of the FSM
} FSMType;

// Function Prototypes
void InitializeFSM(FSMType *FSM);
FSMState NextStateFunction(FSMType *FSM); //, DebounceSwitchFSMDefine *DebounceSwitchFSM
void OutputFunction(FSMType *FSM);// DebounceSwitchFSMDefine *DebounceSwitchFSM

#endif /* FSM_H_ */
