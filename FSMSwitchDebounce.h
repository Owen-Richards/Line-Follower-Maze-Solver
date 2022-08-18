#ifndef FSMSWITCHDEBOUNCE_H_
#define FSMSWITCHDEBOUNCE_H_

#include "Switch.h"

// Constant Definitions
#define ACTIVE_THRESHOLD 10 // Time (in ms) to wait after button press.
#define INACTIVE_THRESHOLD 20 // Time (in ms) to wait after button release.

// Type Definitions
typedef enum {
	WaitingForActive, ValidateActive, WaitingForInactive, ValidateInactive
} DbState;

typedef struct {
    SwitchDefine Switch;                    // Base switch structure (object)
	DbState CurrentState;			        // Current state of the FSM
	uint16_t EventTime;                     // Output: Records time of an event,
    SwitchStatus DebouncedSwitchStatus;     // Output: Current state of debounced switch.
    uint8_t SwitchCycleNotComplete;         // Output: Boolean that indicates if switch has completed FSM cycle.
	uint8_t ActiveThreshold;		        // Time switch must remain Active
	uint8_t InactiveThreshold;	            // Time switch must remain Inactive after being Active
} DebounceSwitchFSMDefine;

// Function Prototypes
void InitializeDebounceSwitchFSM(DebounceSwitchFSMDefine *SwitchFSM,
                                 uint8_t *SwitchPort,uint8_t SwitchBit,
                                 SwitchStatus PortPinIs0Value, SwitchStatus PortPinIs1Value,
                                 uint8_t ActiveThreshold,uint8_t InactiveThreshold);

DbState NextStateFunctionSwitchDebounce(DebounceSwitchFSMDefine *SwitchFSM,uint8_t X0,uint8_t X1);
void OutputFunctionSwitchDebounce(DebounceSwitchFSMDefine *SwitchFSM,uint8_t X0,uint8_t X1);

SwitchStatus ReadDebouncedSwitchStatus(DebounceSwitchFSMDefine *SwitchFSM);

#endif
