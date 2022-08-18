/**
 * @file      PWM.h
 * @brief     Provides low-level functions for generating PWM signals
 ******************************************************************************/

#ifndef PWM_H
#define PWM_H
#include <stdint.h>


/**
 * Initializes PWM output on P2.6 (right motor) using Timer A0 CCR3 interrupt
 * and on P2.7 (left motor) using the Timer A0 CCR4 interrupt
 * Assumes SMCLK has been initialized to 12 MHz
 * @param period the period of the PWM signal in 83.3 us units
 * @param duty3 the desired duty cycle on P2.6 (TA0 CCR3) as a percent (from 0-100)
 * @param duty4 the desired duty cycle on P2.7 (TA0 CCR4) as a percent (from 0-100)
 * @return none
 */
void PWM_Init(uint16_t period, uint16_t duty3, uint16_t duty4);



/**
 * Sets the duty cycle of the PWM output on P2.6 (right motor)
 * @param duty3 the desired duty cycle on P2.6 (changes TA0 CCR3)
 * @return none
 */
void PWM_Duty_Right(uint16_t duty1);


/**
 * Sets the duty cycle of the PWM output on P2.7 (left motor)
 * @param duty4 the desired duty cycle on P2.7 (changes TA0 CCR4)
 * @return none
 */
void PWM_Duty_Left(uint16_t duty4);


#endif
