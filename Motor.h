/**
 * @file      Motor.h
 * @brief     Provides low-level functions for interfacing with the motors
 ******************************************************************************/

#ifndef MOTOR_H
#define MOTOR_H
#include <stdint.h>


/*
 * Motor connections on the robot:
 *   Left Motor:                Right Motor:
 *    - Direction: P5.4         - Direction: P5.5
 *    - PWM:       P2.7         - PWM        P2.6
 *    - Enable:    P3.7         - Enable     P3.6
 */

/**
 * Initialize GPIO pins and PWM for motor output
 * @param none
 * @return none
 */
void Motor_Init(void);

/**
 * Move robot forward by running both motors in the forward direction
 * @param leftDuty: the forward duty cycle of the left motor (P2.7)
 * @param rightDuty: the forward duty cycle of the right motor (P2.6)
 * @return none
 */
void Motor_Forward(uint16_t leftDuty, uint16_t rightDuty);

/**
 * Move robot backwards by running both motors in the reverse direction
 * @param leftDuty: the backwards duty cycle of the left motor (P2.7)
 * @param rightDuty: the backwards duty cycle of the right motor (P2.6)
 * @return none
 */
void Motor_Backward(uint16_t leftDuty, uint16_t rightDuty);

/**
 * Rotate the robot to the left in place by running the left motor backwards and the right motor forwards
 * @param leftDuty: the backwards duty cycle of the left motor (P2.7)
 * @param rightDuty: the forward duty cycle of the right motor (P2.6)
 * @return none
 */
void Motor_Left(uint16_t leftDuty, uint16_t rightDuty);

/**
 * Rotate the robot to the right in place by running the left motor forwards and the right motor backwards
 * @param leftDuty: the forward duty cycle of the left motor (P2.7)
 * @param rightDuty: the backwards duty cycle of the right motor (P2.6)
 * @return none
 */
void Motor_Right(uint16_t leftDuty, uint16_t rightDuty);

/**
 * Stops the robot and puts the motors into sleep mode by setting the enable pins (P3.6 and P3.7)
 * @param none
 * @return none
 */
void Motor_Stop(void);

#endif
