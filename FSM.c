#include "FSM.h"
#include "Reflectance.h"
#include "Bump.h"
#include "Motor.h"
#include "Nokia5110.h"
#include "Clock.h"
#include "bmi160_support.h"

#define FALSE 0
#define TRUE 1

extern uint8_t ReflectanceRead;
extern uint8_t bumpData;

//extern float convertedLux;
//extern struct bmi160_accel_t s_accelXYZ;

extern int lastState;
extern int LiftedUp;
extern int StopSlowNormalLight;

int prevChoice = 0;

void InitializeFSM(FSMType *FSM)
{
    FSM->CurrentState = Center;
}

FSMState NextStateFunction(FSMType *FSM)//, DebounceSwitchFSMDefine *DebounceSwitchFSM
{
    FSMState NextState = FSM->CurrentState;
    //uint8_t DebounceSwitchFSMCycleNotComplete = DebounceSwitchFSM->SwitchCycleNotComplete;

    switch (FSM->CurrentState) {
    case Lost:
        NextState = Wait;
        break;
    case Right:
        NextState = Wait;
        break;
    case Left:
        NextState = Wait;
        break;
    case Center:
        NextState = Wait;
        break;
    case Stop_Bump:
        NextState = Wait;
        break;
    case SharpRight:
        NextState = Wait;
        break;
    case SharpLeft:
        NextState = Wait;
        break;
    case Choose:
        NextState = Wait;
        break;
    case Finish:
        NextState = Wait;
        break;
    case Wait:
        if (bumpData != 0x00 ) {
            NextState = Stop_Bump;
        }
        else if (ReflectanceRead == 204 || ReflectanceRead == 196 || ReflectanceRead == 68 && lastState != 1 || ReflectanceRead == 70 && lastState != 1 || ReflectanceRead == 198 && lastState != 1 || ReflectanceRead == 102 || ReflectanceRead == 38 || ReflectanceRead == 51 || ReflectanceRead == 17 || ReflectanceRead == 19 || ReflectanceRead == 25 || ReflectanceRead == 49 || ReflectanceRead == 145 || ReflectanceRead == 152 || ReflectanceRead == 153 || ReflectanceRead == 157 ||  ReflectanceRead == 140 ||  ReflectanceRead == 204 || ReflectanceRead == 137 || ReflectanceRead == 230 || ReflectanceRead == 136 || ReflectanceRead == 185 || ReflectanceRead == 236 || ReflectanceRead == 68 || ReflectanceRead == 38 || ReflectanceRead == 34 || ReflectanceRead == 51 || ReflectanceRead == 17 || ReflectanceRead == 25){
            NextState = Finish;
        }
        else if (ReflectanceRead == 0){
            NextState = Lost;
        }
        else if (ReflectanceRead == 128 || ReflectanceRead == 192 || ReflectanceRead == 64 || ReflectanceRead == 96 || ReflectanceRead == 32 || ReflectanceRead == 48 || ReflectanceRead == 16){
            NextState = Left;
        }
        else if (ReflectanceRead == 8 || ReflectanceRead == 12 || ReflectanceRead == 4 || ReflectanceRead == 6 || ReflectanceRead == 2 || ReflectanceRead == 3 || ReflectanceRead == 1){
            NextState = Right;
        }
        else if (ReflectanceRead == 24){
            NextState = Center;
        }
        else if (ReflectanceRead == 31 || ReflectanceRead == 15 || ReflectanceRead == 7 || ReflectanceRead == 63 ||ReflectanceRead == 30 || ReflectanceRead == 20 || ReflectanceRead == 70 || ReflectanceRead == 68){
            NextState = SharpRight;
        }
        else if (ReflectanceRead == 248 || ReflectanceRead == 240 || ReflectanceRead == 252 || ReflectanceRead == 224 || ReflectanceRead == 120 || ReflectanceRead == 124 || ReflectanceRead == 56){
            NextState = SharpLeft;
        }
        else {//choose right
            NextState = Choose;
        }
        break;

    }
    return NextState;
}

void OutputFunction(FSMType *FSM)//, DebounceSwitchFSMDefine *DebounceSwitchFSM
{
    //if (DebounceSwitchFSM->SwitchCycleNotComplete == FALSE) {
    //    DebounceSwitchFSM->SwitchCycleNotComplete = TRUE;
    //}
    switch (FSM->CurrentState) {
    case Wait:
        break;
    case Stop_Bump:
        //all 4 lights turn on
        Nokia5110_Clear();
        Nokia5110_SetCursor(0, 1);
        Nokia5110_OutString("Hit Object  Stop Motor");
        GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN6); //LEDBL
        GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN7); //LEDBR
        GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN5); //LEDFR
        GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN0); //LEDFL
        Motor_Stop();
        break;
    case Lost:
        //brake lights are on
        GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN6); //LEDBL
        GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN7); //LEDBR
        GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN5); //LEDFR
        GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN0); //LEDFL
        if (lastState == 1){
            Nokia5110_Clear();
            Nokia5110_SetCursor(0, 1);
            Nokia5110_OutString("Lost Right");
            Motor_Right(14,14);
        }
        else if (lastState == 2) {
            Nokia5110_Clear();
            Nokia5110_SetCursor(0, 1);
            Nokia5110_OutString("Lost Left");
            Motor_Right(14,14);
        }
        else if (lastState == 3) {
            Nokia5110_Clear();
            Nokia5110_SetCursor(0, 1);
            Nokia5110_OutString("Lost Center");
            while(ReflectanceRead != 24){
                Motor_Right(14,14);
            }
        }
        break;
    case Right:
        GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN5); //LEDFR
        GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN0); //LEDFL
        GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN6); //LEDBL
        GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN7); //LEDBR
        lastState = 1;
        if (ReflectanceRead == 8){
            Nokia5110_Clear();
            Nokia5110_SetCursor(0, 1);
            Nokia5110_OutString("Tiny Right");
            Motor_Forward(16, 10);

        }
        if (ReflectanceRead == 12){
            Nokia5110_Clear();
            Nokia5110_SetCursor(0, 1);
            Nokia5110_OutString("Less tiny Right");
            Motor_Forward(14, 8);
        }
        if (ReflectanceRead == 4){
            Nokia5110_Clear();
            Nokia5110_SetCursor(0, 1);
            Nokia5110_OutString("Quite Right");
            Motor_Forward(14, 6);
        }
        if (ReflectanceRead == 6){
            Nokia5110_Clear();
            Nokia5110_SetCursor(0, 1);
            Nokia5110_OutString("Half Right");
            Motor_Forward(14, 4);
        }
        if (ReflectanceRead == 2){
            Nokia5110_Clear();
            Nokia5110_SetCursor(0, 1);
            Nokia5110_OutString("Big Right");
            Motor_Forward(14, 4);
        }
        if (ReflectanceRead == 3){
            Nokia5110_Clear();
            Nokia5110_SetCursor(0, 1);
            Nokia5110_OutString("Full Right");
            Motor_Right(10, 10);
        }
        if (ReflectanceRead == 1){
            Nokia5110_Clear();
            Nokia5110_SetCursor(0, 1);
            Nokia5110_OutString("Most Right");
            Motor_Right(10, 10);
        }
        break;

    case Left:

        GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN0); //LEDFL
        GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN5); //LEDFR
        GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN6); //LEDBL
        GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN7); //LEDBR
        lastState = 2;
        if (ReflectanceRead == 16){
            Nokia5110_Clear();
            Nokia5110_SetCursor(0, 1);
            Nokia5110_OutString("Tiny Left");
            Motor_Forward(10, 16);
        }
        if (ReflectanceRead == 48){
            Nokia5110_Clear();
            Nokia5110_SetCursor(0, 1);
            Nokia5110_OutString("Less tiny Left");
            Motor_Forward(8, 14);
        }
        if (ReflectanceRead == 32){
            Nokia5110_Clear();
            Nokia5110_SetCursor(0, 1);
            Nokia5110_OutString("Quite Left");
            Motor_Forward(6, 14);
        }
        if (ReflectanceRead == 96){
            Nokia5110_Clear();
            Nokia5110_SetCursor(0, 1);
            Nokia5110_OutString("Half Left");
            Motor_Forward(4, 14);
        }
        if (ReflectanceRead == 64){
            Nokia5110_Clear();
            Nokia5110_SetCursor(0, 1);
            Nokia5110_OutString("Big Left");
            Motor_Forward(2, 14);
        }
        if (ReflectanceRead == 192){
            Nokia5110_Clear();
            Nokia5110_SetCursor(0, 1);
            Nokia5110_OutString("Full Left");
            Motor_Left(12, 12);
        }
        if (ReflectanceRead == 128){
            Nokia5110_Clear();
            Nokia5110_SetCursor(0, 1);
            Nokia5110_OutString("Most Left");
            Motor_Left(12,12);
        }
        break;
    case Center:
        // front lights on
        Nokia5110_Clear();
        Nokia5110_SetCursor(0, 1);
        Nokia5110_OutString("Center");
        lastState = 3;
        GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN5); //LEDFR
        GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN0); //LEDFL
        GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN6); //LEDBL
        GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN7); //LEDBR
        Motor_Forward(15, 15);
        break;
    case SharpRight:
        Nokia5110_Clear();
        Nokia5110_SetCursor(0, 1);
        Nokia5110_OutString("Sharp Right");
        GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN5); //LEDFR
        GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN0); //LEDFL
        GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN6); //LEDBL
        GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN7); //LEDBR
        lastState = 1;
        Motor_Forward(15,15);
        while(ReflectanceRead != 24){
            Motor_Right(15, 15);
            if (ReflectanceRead == 128 || ReflectanceRead == 192 || ReflectanceRead == 64 || ReflectanceRead == 96 || ReflectanceRead == 32 || ReflectanceRead == 48 || ReflectanceRead == 16 || ReflectanceRead == 8 || ReflectanceRead == 12 || ReflectanceRead == 4 || ReflectanceRead == 6 || ReflectanceRead == 2 || ReflectanceRead == 3 || ReflectanceRead == 1){
                break;
            }
        }
        break;
    case SharpLeft:
        Nokia5110_Clear();
        Nokia5110_SetCursor(0, 1);
        Nokia5110_OutString("Sharp Left");
        GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN0); //LEDFL
        GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN5); //LEDFR
        GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN6); //LEDBL
        GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN7); //LEDBR
        lastState = 2;
        Motor_Forward(15,15);
        while(ReflectanceRead != 24){
            Motor_Left(15, 15);
            if (ReflectanceRead == 128 || ReflectanceRead == 192 || ReflectanceRead == 64 || ReflectanceRead == 96 || ReflectanceRead == 32 || ReflectanceRead == 48 || ReflectanceRead == 16 || ReflectanceRead == 8 || ReflectanceRead == 12 || ReflectanceRead == 4 || ReflectanceRead == 6 || ReflectanceRead == 2 || ReflectanceRead == 3 || ReflectanceRead == 1){
                break;
            }
        }
        break;
    case Choose:
        Nokia5110_Clear();
        Nokia5110_SetCursor(0, 1);
        Nokia5110_OutString("Choose Right");
        GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN5); //LEDFR
        GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN0); //LEDFL
        GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN6); //LEDBL
        GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN7); //LEDBR
        if (ReflectanceRead == 255){
            while(ReflectanceRead != 24){
                Motor_Right(12, 12);
            }
        }
        else{
            Motor_Right(12, 12);
        }
        break;
    case Finish:
        Nokia5110_Clear();
        Nokia5110_SetCursor(0, 1);
        Nokia5110_OutString("Woop Woop    Finished");
        GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN6); //LEDBL
        GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN7); //LEDBR
        GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN5); //LEDFR
        GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN0); //LEDFL
        Motor_Stop();
        break;
        }
   }
