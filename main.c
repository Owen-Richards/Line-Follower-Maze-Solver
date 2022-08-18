//*****************************************************************************
//
// Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//  Redistributions of source code must retain the above copyright
//  notice, this list of conditions and the following disclaimer.
//
//  Redistributions in binary form must reproduce the above copyright
//  notice, this list of conditions and the following disclaimer in the
//  documentation and/or other materials provided with the
//  distribution.
//
//  Neither the name of Texas Instruments Incorporated nor the names of
//  its contributors may be used to endorse or promote products derived
//  from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// MSP432 Low Power main.c
//
//      Description: Source code for the implementation of the Bosch BoosterPack with
//      an MSP432P401R launchpad for low power consumption. BoosterPack includes:
//      - Inertial Measurement Unit (IMU) sensor with an accelerometer and gyroscope
//      - Magnetometer
//      - Environmental sensor with pressure, ambient temperature and humidity
//      - Ambient light sensor
//      - Infrared temperature sensor
//
// Adapted by Michael Arriete
//
//****************************************************************************
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <msp432.h>
#include "stdio.h"
#include "i2c_driver.h"
#include "demo_sysctl.h"
#include "bmi160_support.h"
#include "bme280_support.h"
#include "opt3001.h"
#include "uart_driver.h"
//
///* DriverLib Includes */
#include "driverlib.h"

/* Standard Includes */
#include <stdio.h>

/* Project Includes */
#include "Clock.h"
#include "Launchpad.h"
#include "TimerA1.h"
#include "Reflectance.h"
#include "Bump.h"
#include "msp.h"
#include "interrupt.h"
#include "Motor.h"
#include "FSM.h"
#include "SensorFSM.h"
#include "Nokia5110.h"
#include "Switch.h"
#include "PortPins.h"
#include "PushButton.h"

//***** Definitions *****
#define CPU_FREQ                    (48000000)

//***** Function Prototypes *****

void startWakeUpTimerA(uint16_t ulClockMS);
void stopWakeUpTimerA(void);


const uint8_t Enemy[] = {
                         0x42, 0x4D, 0xC6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00,
                         0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80,
                         0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
                         0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F,
                         0x0F, 0x00, 0x00, 0xF0, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
                         0xFF, 0x0F, 0xF0, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00,
                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF
};


// BMI160/BMM150
BMI160_RETURN_FUNCTION_TYPE returnValue;
struct bmi160_gyro_t        s_gyroXYZ;
struct bmi160_accel_t       s_accelXYZ;
struct bmi160_mag_xyz_s32_t s_magcompXYZ;
//
//// BME280
s32 returnRslt;

// OPT3001
uint16_t rawData;
float    convertedLux;


//Calibration off-sets
int8_t accel_off_x;
int8_t accel_off_y;
int8_t accel_off_z;
s16 gyro_off_x;
s16 gyro_off_y;
s16 gyro_off_z;



int count = 0;
int lastState = 1;
uint8_t ReflectanceRead;
uint8_t bumpData;
FSMTypeSensor Sensor_FSM;
FSMType LED_FSM;
uint64_t delaycounter = 0;
int LiftedUp = 0;
int StopSlowNormalLight = 3;


void Task(void){
    if(count % 10 == 0){
        Reflectance_Start();
        }
    if(count % 10 == 1){
        ReflectanceRead = Reflectance_End();
    }
    if(count % 10 == 2){
        bumpData = Bump_Read();
    }
    count++;
}

/***********************************************************
  Function:
 */
int main(void)
{
    volatile uint32_t index;

    //Initialize uart
    uartInit();

    // Initialize i2c
    initI2C();

    MAP_Interrupt_enableMaster();
    // Init
        GPIO_setAsOutputPin(GPIO_PORT_P8, GPIO_PIN6); //LEDBL
        GPIO_setAsOutputPin(GPIO_PORT_P8, GPIO_PIN7); //LEDBR
        GPIO_setAsOutputPin(GPIO_PORT_P8, GPIO_PIN5); //LEDFR
        GPIO_setAsOutputPin(GPIO_PORT_P8, GPIO_PIN0); //LEDFL
        Clock_Init();
        Bump_Init();
        Motor_Init();

    InitializeFSM(&LED_FSM);

    SwitchDefine PushButtonS1;
    SwitchDefine PushButtonS2;
    //InitializeLEDPortPin();
    InitializePushButtonPortPins();

    InitializeSwitch(&PushButtonS1, (uint8_t *) &(PUSHBUTTON_S1_PORT->IN),
                                 (uint8_t) PUSHBUTTON_S1_BIT, Active, Inactive);
    InitializeSwitch(&PushButtonS2, (uint8_t *) &(PUSHBUTTON_S2_PORT->IN),
                                         (uint8_t) PUSHBUTTON_S2_BIT, Active, Inactive);

        TimerA1_Init(&Task, 500);
        Nokia5110_Init();
    while(1)
    {
        if (ReadSwitchStatus(&PushButtonS1)){
            LiftedUp = 0;
        }
        if (ReadSwitchStatus(&PushButtonS2)){
            LiftedUp = 1;
        }

        LED_FSM.CurrentState = NextStateFunction(&LED_FSM);

        //Produce outputs based on current state
        OutputFunction(&LED_FSM);

    }
}

///***********************************************************
//  Function:
// */
void startWakeUpTimerA(uint16_t ulClockMS)
{
    ulClockMS = (ulClockMS * 32768)/1000;

    /* TimerA UpMode Configuration Parameter */
    Timer_A_UpModeConfig upConfig =
    {
            TIMER_A_CLOCKSOURCE_ACLK,              // ACLK Clock Source
            TIMER_A_CLOCKSOURCE_DIVIDER_1,         // ACLK/1 = 32KHz
            ulClockMS,                             // tick period
            TIMER_A_TAIE_INTERRUPT_DISABLE,        // Disable Timer interrupt
            TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE ,   // Enable CCR0 interrupt
            TIMER_A_SKIP_CLEAR                     // Clear value
    };

    MAP_Timer_A_configureUpMode(TIMER_A0_BASE, &upConfig);
    MAP_Timer_A_enableCaptureCompareInterrupt(TIMER_A0_BASE,
            TIMER_A_CAPTURECOMPARE_REGISTER_0);

    MAP_Interrupt_enableInterrupt(INT_TA0_0);
    MAP_Timer_A_startCounter(TIMER_A0_BASE,TIMER_A_UP_MODE);
}
//
///***********************************************************
//  Function:
// */
void stopWakeUpTimerA(void)
{
    MAP_Interrupt_disableInterrupt(INT_TA0_0);
    MAP_Timer_A_stopTimer(TIMER_A0_BASE);
}
