#include "PushButton.h"

void InitializePushButtonPortPins(void)
{
    // Configure port pin for pushbutton
    ENABLE_PULL_UP_PULL_DOWN_RESISTORS_S1;
    ENABLE_PULL_UP_PULL_DOWN_RESISTORS_S2;
    SELECT_PULL_UP_RESISTORS_S1;
    SELECT_PULL_UP_RESISTORS_S2;
    SET_PUSHBUTTON_S1_TO_AN_INPUT;
    SET_PUSHBUTTON_S2_TO_AN_INPUT;
}
