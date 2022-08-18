#ifndef SWITCH_H_
#define SWITCH_H_

#include <driverlib.h>
#include <stdint.h>

typedef enum {
    Inactive,
    Active
} SwitchStatus;

typedef struct {
    uint8_t *    SwitchPort;                // Input port associated with switch
    uint8_t      SwitchPortBit;             // Bit mask for port pin associated with switch
    SwitchStatus Logic0Value;               // Switch state associated with logic 0.
    SwitchStatus Logic1Value;               // Switch state associated with logic 1.
} SwitchDefine;

// Function Prototypes
void InitializeSwitch(SwitchDefine *Switch,uint8_t *SwitchPort,uint8_t SwitchBit,
                      SwitchStatus Logic0Value, SwitchStatus Logic1Value);

//This function returns the instantaneous value of the selected switch
SwitchStatus ReadSwitchStatus(SwitchDefine *Switch);

#endif /* SWITCH_H_ */
