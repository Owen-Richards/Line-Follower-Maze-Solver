#ifndef BUMP_H
#define BUMP_H
#include <stdint.h>
/*
 * Initialize bump sensor pins as GPIO inputs with pull up resistors
 * Port 4, Pins 0, 2, 3, 5, 6, and 7
 * @param none
 * @return none
 */
void Bump_Init(void);

/*
 * Initializes bump sensor pins and the port pin interrupts
 */
void Bump_Interrupt_Init(void(*task)(uint8_t));

/*
 * Read the state of the bump switches
 * @param none
 * @return uint8_t variable, bits 0-5 correspond to
 * the values of bump switches 0-5 (right to left on the robot)
 */
uint8_t Bump_Read(void);

#endif
