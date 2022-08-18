#ifndef TIMERA1_H
#define TIMERA1_H

/*
 * Initialize Timer A1 at 500 kHz to run a periodic interrupt
 * @param task: function pointer to user function to run on interrupt
 * @param period: Timer period
 * @note Timer source is SMCLK, assumes SMCLK is initialized at 12 MHz
 */
void TimerA1_Init(void (*task)(void), uint16_t period);

/*
 * Stops periodic interrupt on Timer A1
 * @param none
 * @return none
 */
void TimerA1_Stop(void);

/*
 * ISR for Timer A1 Periodic Interrupt from CCR0
 */
void TA1_0_IRQHandler(void);

#endif
