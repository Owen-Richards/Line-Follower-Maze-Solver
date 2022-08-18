/* DriverLib Includes */
#include "driverlib.h"

/* Standard Includes */
#include <stdint.h>

/* Project Includes */
#include "PWM.h"
#include "gpio.h"

/* Application Defines  */
int TIMERA1_PERIOD = 0xFFFF;

/* Timer_A UpDown Configuration Parameter */
Timer_A_UpDownModeConfig upDownConfig =
{
        TIMER_A_CLOCKSOURCE_SMCLK,               // SMCLK Clock Source
        TIMER_A_CLOCKSOURCE_DIVIDER_1,          // ACLK/1 = 32kHz
        0xFFFF,                         // 127 tick period
        TIMER_A_TAIE_INTERRUPT_DISABLE,         // Disable Timer interrupt
        TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE,    // Disable CCR0 interrupt
        TIMER_A_DO_CLEAR                        // Clear value
};

/* Timer_A Compare Configuration Parameter  (PWM1) */
Timer_A_CompareModeConfig compareConfig_PWM1 =
{
        TIMER_A_CAPTURECOMPARE_REGISTER_3,          // Use CCR1
        TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE,   // Disable CCR interrupt
        TIMER_A_OUTPUTMODE_TOGGLE_SET,              // Toggle output bit
        0xFFFF                              // Initial 0% Duty Cycle
};

Timer_A_CompareModeConfig compareConfig_PWM2 =
{
        TIMER_A_CAPTURECOMPARE_REGISTER_4,          // Use CCR2
        TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE,   // Disable CCR interrupt
        TIMER_A_OUTPUTMODE_TOGGLE_SET,              // Toggle output bit
        0xFFFF                              // Initial 0% Duty Cycle
};

// converts Duty cycle from 0-100 to a CCR value
uint16_t Duty_To_CCR(uint16_t duty) {
    return (((100-duty)*TIMERA1_PERIOD)/100);
}

/**
 * Initializes PWM output on P2.6 (right motor) using Timer A0 CCR3 interrupt
 * and on P2.7 (left motor) using the Timer A0 CCR4 interrupt
 * Assumes SMCLK has been initialized to 12 MHz
 * @param period the period of the PWM signal in 83.3 us units
 * @param duty3 the desired duty cycle on P2.6 (TA0 CCR3) as a percent (from 0-100)
 * @param duty4 the desired duty cycle on P2.7 (TA0 CCR4) as a percent (from 0-100)
 * @return none
 */
void PWM_Init(uint16_t period, uint16_t duty3, uint16_t duty4){

    TIMERA1_PERIOD = period;

    upDownConfig.timerPeriod = period;

    compareConfig_PWM1.compareValue = Duty_To_CCR(duty3);

    compareConfig_PWM2.compareValue = Duty_To_CCR(duty4);

    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2,
         GPIO_PIN6 | GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);

    // Configure Timer_A1 for UpDown Mode
    Timer_A_configureUpDownMode(TIMER_A0_BASE, &upDownConfig);

    // Start TimerA1 in UpDown Mode
    Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_UPDOWN_MODE);

    // Initialize compare registers to generate PWM1
    Timer_A_initCompare(TIMER_A0_BASE, &compareConfig_PWM1);

    // Initialize compare registers to generate PWM2
    Timer_A_initCompare(TIMER_A0_BASE, &compareConfig_PWM2);
}

void PWM_Duty_Right(uint16_t duty1){
    // Convert Duty Cycle into the appropriate CCR Value
    uint16_t CCR_Value = Duty_To_CCR(duty1);

    // Modify the CCR Value in the configuration
    compareConfig_PWM1.compareValue = CCR_Value;

    // Initialize the timer with the modified configuration
    Timer_A_initCompare(TIMER_A0_BASE, &compareConfig_PWM1);
}

void PWM_Duty_Left(uint16_t duty4){
    // Convert Duty Cycle into the appropriate CCR Value
    uint16_t CCR_Value = Duty_To_CCR(duty4);

    // Modify the CCR Value in the configuration
    compareConfig_PWM2.compareValue = CCR_Value;

    // Initialize the timer with the modified configuration
    Timer_A_initCompare(TIMER_A0_BASE, &compareConfig_PWM2);
}
