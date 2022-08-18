#include "Switch.h"

SwitchStatus ReadSwitchStatus(SwitchDefine *Switch)
{
    volatile uint8_t SwitchValue;

    SwitchValue = *(Switch->SwitchPort) & Switch->SwitchPortBit;
    if (SwitchValue) {
        return Switch->Logic1Value;
    }
    else {
        return Switch->Logic0Value;
    }
}

void InitializeSwitch(SwitchDefine *Switch,uint8_t *SwitchPort,uint8_t SwitchBit,
        SwitchStatus Logic0Value, SwitchStatus Logic1Value)
{
    Switch->SwitchPort    = SwitchPort;
    Switch->SwitchPortBit = SwitchBit;
    Switch->Logic0Value   = Logic0Value;
    Switch->Logic1Value   = Logic1Value;
}
