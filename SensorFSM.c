#include "SensorFSM.h"
#include "Motor.h"
#include <stdio.h>
#include "bmi160_support.h"
#include "Reflectance.h"
#include "Bump.h"
#include "Nokia5110.h"
#include "Clock.h"
#include "bmi160_support.h"

// Global Variable in main, then sensorFSM updates the global variable, and variable is used in FSM.
#define FALSE 0
#define TRUE 1

extern float convertedLux;
extern struct bmi160_accel_t s_accelXYZ;

extern int LiftedUp;
extern int StopSlowNormalLight;

int LuxStop = 50;
int LuxSlow = 150;

void InitializeSensorFSM(FSMTypeSensor *FSM)
{
    FSM->CurrentState = Normal_Operation;
    Nokia5110_SetCursor(0, 1);
}

FSMState1 NextSensorStateFunction(FSMTypeSensor *FSM)
{
    FSMState1 NextState = FSM->CurrentState;

    switch (FSM->CurrentState) {
    case Normal_Operation:
        NextState = SensorWait;
        break;
    case Take_It_Slow:
        NextState = SensorWait;
        break;
    case Stop:
        NextState = SensorWait;
        break;
    case SensorWait:
        if(convertedLux < LuxSlow && convertedLux > LuxStop){
            NextState = Take_It_Slow;
        }
        else if( s_accelXYZ.z > 20000 || convertedLux <= LuxStop){ //s_accelXYZ.z < 700 ||
            NextState = Stop;
        } else{
            NextState = Normal_Operation;
        }
        break;
    }

    return NextState;
}

void OutputSensorFunction(FSMTypeSensor *FSM)
{
    switch (FSM->CurrentState) {
    case SensorWait:
        break;
    case Normal_Operation:
        StopSlowNormalLight = 3;
        break;
    case Take_It_Slow:
        StopSlowNormalLight = 2;
        break;
    case Stop:
        GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN6); //LEDBL
        GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN7); //LEDBR
        GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN5); //LEDFR
        GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN0); //LEDFL
        Motor_Stop();
        if ( s_accelXYZ.z > 20000){ //s_accelXYZ.z < 700 ||
            if(LiftedUp == 0){
                LiftedUp = 1;
            }
            else{
                LiftedUp = 0;
            }
        }
        if (convertedLux <= LuxStop){
            StopSlowNormalLight = 1;
        }
        break;
    }
}
