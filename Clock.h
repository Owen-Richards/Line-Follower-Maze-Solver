/**
 * @file      Clock.h
 * @brief     Provide initialization function for a 48 MHz clock
 ******************************************************************************/
#ifndef CLOCK_H
#define CLOCK_H
#include <stdint.h>
/**
 * Initializes the HFXT Oscillator in the highest power state to allow for 48 MHz operation
 * @param none
 * @return none
 */
void HFXT_Init(void);

/**
 * Initializes the MCLK and SMCLK using the HFXT Oscillator as clock source
 * Sets MCLK frequency to 48 MHz and SMCLK freqency to 12 MHz
 * @param none
 * @return none
 */
void Clock_Init(void);

/**
 * Delay n microseconds
 * @param n the number of microseconds to wait
 * @return none
 */
void Clock_Delay1us(uint32_t n);

/**
 * Simple delay function which delays about n milliseconds.
 * It is implemented with a nested for-loop and is very approximate.
 * @param  n is the number of msec to wait
 * @return none
 * @note This function assumes a 48 MHz clock.
 * This implementation is not very accurate.
 * To improve accuracy, you could tune this function
 * by adjusting the constant within the implementation
 * found in the <b>Clock.c</b> file.
 * For a more accurate time delay, you could use the SysTick module.
 * @brief  Software implementation of a busy-wait delay
 */
void Clock_Delay1ms(uint32_t n);

#endif
