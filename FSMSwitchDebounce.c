#include <FSMSwitchDebounce.h>

#define FALSE 0
#define TRUE 1

extern unsigned int g1msTimer;

void InitializeDebounceSwitchFSM(DebounceSwitchFSMDefine *SwitchFSM,
                                 uint8_t *SwitchPort,uint8_t SwitchBit,
                                 SwitchStatus PortPinIs0Value, SwitchStatus PortPinIs1Value,
                                 uint8_t ActiveThreshold,uint8_t InactiveThreshold)
{
    SwitchDefine *Switch = &(SwitchFSM->Switch);

    InitializeSwitch(Switch,SwitchPort,SwitchBit,PortPinIs0Value,PortPinIs1Value);
    SwitchFSM->CurrentState = WaitingForActive;
    SwitchFSM->ActiveThreshold = ActiveThreshold; // units equal milliseconds
    SwitchFSM->InactiveThreshold = InactiveThreshold; // units equal milliseconds
    SwitchFSM->EventTime = 0;
    SwitchFSM->DebouncedSwitchStatus = Inactive;
    SwitchFSM->SwitchCycleNotComplete = (uint8_t) TRUE;
}

DbState NextStateFunctionSwitchDebounce(DebounceSwitchFSMDefine *SwitchFSM,uint8_t X0,uint8_t X1)
{
/*
 * This function implements a 4-state Mealy state machine:
 *
 * WaitingForActive (WFA): 		The switch is currently in the inactive state and awaiting a transition to the
 * 							active state.
 * ValidateActive (VA): 	The state has transitioned to the active state, but the elapsed time from the
 * 							transition to the current time (in g1msTimer) has not exceeded the threshold,
 * 							HoldTime.
 * WaitingForInactive (WFI):		The switch is currently in the active state and awaiting a transition to the
 * 							inactive state.
 * ValidateInactive (VI):		The state has transitioned to the inactive state, but the elapsed time from the
 * 							transition to the current time (in g1msTimer) has not exceeded the threshold,
 * 							ReleaseTime.
 *
 * The state machine has two inputs:
 *
 * X1:	This input is a logical condition based on the elapsed time from the transition from the inactive state
 * 		to the active state (or vice-versa). X1 = true implies the elapsed time is greater than the threshold.
 * X0:	This input is a logical condition based on the state of the switch (high or low). X0 = true implies
 * 		that the switch is in the active (High) state.
 *
 * State Transition Table:
 * 		NS
 * CS	X1X0 = 	FF  FT  TF  TT
 * --------------------------------
 * WFA			WFA VA WFA VA
 * VA			WFA VA WFA WFI
 * WFI			VI WFI VI WFI
 * VI			VI WFI WFA WFI
 *
 */
	DbState NextState;

	switch (SwitchFSM->CurrentState) {
		case WaitingForActive:
			if (X0 == TRUE) {NextState = ValidateActive;}
			else {NextState = WaitingForActive;}
		break;
		case ValidateActive:
			if (X0 == FALSE) {NextState = WaitingForActive;}
			else {
				if (X1 == TRUE) {NextState = WaitingForInactive;}
				else {NextState = ValidateActive;}
			}
		break;
		case WaitingForInactive:
			if (X0 == FALSE) {NextState = ValidateInactive;}
			else {NextState = WaitingForInactive;}
		break;
		case ValidateInactive:
			if (X0 == TRUE) {NextState = WaitingForInactive;}
			else {
				if (X1 == TRUE) {NextState = WaitingForActive;}
				else {NextState = ValidateInactive;}
			}
		break;
		default: NextState = WaitingForActive;
	}
	
	return NextState;
}

void OutputFunctionSwitchDebounce(DebounceSwitchFSMDefine *SwitchFSM,uint8_t X0,uint8_t X1)
{
    switch (SwitchFSM->CurrentState) {
        case WaitingForActive:
            if (X0 == TRUE) { SwitchFSM->EventTime = g1msTimer; }
            SwitchFSM->DebouncedSwitchStatus = Inactive;
        break;
        case ValidateActive:
            if ((X1 == TRUE) && (X0 == TRUE)) {SwitchFSM->DebouncedSwitchStatus = Active;}
            else {SwitchFSM->DebouncedSwitchStatus = Inactive;}
        break;
        case WaitingForInactive:
            if (X0 == FALSE) { SwitchFSM->EventTime = g1msTimer; }
            SwitchFSM->DebouncedSwitchStatus = Active;
        break;
        case ValidateInactive:
            if ((X1 == TRUE) && (X0 == FALSE)) {
                SwitchFSM->DebouncedSwitchStatus = Inactive;
                SwitchFSM->SwitchCycleNotComplete = (uint8_t) FALSE;
            }
            else {SwitchFSM->DebouncedSwitchStatus = Active;}
        break;
        //default: ;
    }
}

SwitchStatus ReadDebouncedSwitchStatus(DebounceSwitchFSMDefine *SwitchFSM)
{
    uint8_t X1 = FALSE;
    uint8_t X0 = FALSE;
    SwitchStatus CurrentSwitchStatus;
    uint16_t ElapsedTime = 0;

    // First, determine the current inputs, X1 and X0.
    ElapsedTime = (uint16_t) (g1msTimer-SwitchFSM->EventTime);
    if (SwitchFSM->CurrentState == ValidateActive) {
        if (ElapsedTime > SwitchFSM->ActiveThreshold) {X1 = TRUE;}
        else {X1 = FALSE;}
    }
    else if (SwitchFSM->CurrentState == ValidateInactive){
        if (ElapsedTime > SwitchFSM->InactiveThreshold) {X1 = TRUE;}
        else {X1 = FALSE;}
    }

    CurrentSwitchStatus = ReadSwitchStatus((SwitchDefine *) SwitchFSM);
    if (CurrentSwitchStatus == Active) {X0 = TRUE;}
    else {X0 = FALSE;}

    // Perform the output function based on the inputs and current state.
    OutputFunctionSwitchDebounce(SwitchFSM,X0,X1);

    // Next, based on the input values and the current state, determine the next state.
    SwitchFSM->CurrentState = NextStateFunctionSwitchDebounce(SwitchFSM,X0,X1);

    return SwitchFSM->DebouncedSwitchStatus;
}
