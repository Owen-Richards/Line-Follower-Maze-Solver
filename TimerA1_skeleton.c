/* DriverLib Includes */
#include "driverlib.h"

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>

/* Project Includes */
#include "TimerA1.h"
#include "timer_a.h"
#include "Bump.h"

// Pointer to user function that gets called on timer interrupt

void (*TimerTask)(void);

// Initializes Timer A1 in up mode and triggers a periodic interrupt at a desired frequency
//This function will initialize the TimerA1 base module in Up mode,
//sourced from the SMCLK (assumed to be running at 12 MHz) with the required input divider
//to give the timer a 500 kHz frequency.
//This function should also enable the CCR0 interrupt and clear and start the timer’s counter.
void TimerA1_Init(void(*task)(void), uint16_t period){
    // initialize the TimerA1 base module in the Up mode
    // enable the CCR0 interrupt and clear the start the timer's counter
    TimerTask = task;
    Timer_A_UpModeConfig config = {
        TIMER_A_CLOCKSOURCE_SMCLK,
        TIMER_A_CLOCKSOURCE_DIVIDER_24,
        period,
        TIMER_A_TAIE_INTERRUPT_ENABLE,
        TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE,
        TIMER_A_DO_CLEAR,
    };
    Timer_A_configureUpMode(TIMER_A1_BASE, &config);
    Interrupt_enableInterrupt ( INT_TA1_0 );
    Timer_A_startCounter(TIMER_A1_BASE, TIMER_A_UP_MODE);
}

// stops Timer A1
// timer is the instance of the Timer_A module.
void TimerA1_Stop(void){
    //Timer_A_stopTimer(TIMER_A1_BASE);
    uint16_t ctl = TIMER_A1->CTL; // ctl is the Timer A1 control
    TIMER_A1->CTL = ctl & 0xFFCF; // ctl is masked with 0xFFCF
}

// ISR function for Timer A1 periodic interrupt
void TA1_0_IRQHandler(void){

    //TimerA1_Init(task, 1000);
    //write this for Interrupt Module Race-Day
    (*TimerTask)();
    Timer_A_clearCaptureCompareInterrupt(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_0); // This clears it
    //Timer_A_clearInterruptFlag(TIMER_A1);
    // this calls it
    // clear interrupt flags
    //Timer_A_clearInterruptFlag(TIMER_A1);

}
