/* DriverLib Includes */
#include "driverlib.h"
#include "msp.h"

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>

/* Project Includes */
#include "Bump.h"

// Define statements for bump switch pins
#define BUMP_PORT   GPIO_PORT_P4
#define BUMP0       GPIO_PIN0   // P4.0
#define BUMP1       GPIO_PIN2   // P4.2
#define BUMP2       GPIO_PIN3   // P4.3
#define BUMP3       GPIO_PIN5   // P4.5
#define BUMP4       GPIO_PIN6   // P4.6
#define BUMP5       GPIO_PIN7   // P4.7
#define BUMP_PINS   (BUMP0 | BUMP1 | BUMP2| BUMP3| BUMP4 | BUMP5)

// Initialize the bump switch pins as GPIO inputs with pull up resistors
// Switches are active low
void Bump_Init(void){
    //Write this for Interrupt Module warm-up
    GPIO_setAsInputPinWithPullUpResistor(BUMP_PORT, BUMP_PINS);
}

// reads values of bump switches
//gives result with positive logic
uint8_t Bump_Read(void){
    uint8_t bump0 = GPIO_getInputPinValue(BUMP_PORT, BUMP0);
    uint8_t bump1 = GPIO_getInputPinValue(BUMP_PORT, BUMP1);
    uint8_t bump2 = GPIO_getInputPinValue(BUMP_PORT, BUMP2);
    uint8_t bump3 = GPIO_getInputPinValue(BUMP_PORT, BUMP3);
    uint8_t bump4 = GPIO_getInputPinValue(BUMP_PORT, BUMP4);
    uint8_t bump5 = GPIO_getInputPinValue(BUMP_PORT, BUMP5);
    //write this for Interrupt Module warm-up
    bump0 = ~bump0; // Negate the bumps
    bump1 = ~bump1;
    bump2 = ~bump2;
    bump3 = ~bump3;
    bump4 = ~bump4;
    bump5 = ~bump5;

    bump0 = bump0 & 1; // mask the bump with 1
    bump1 = bump1 & 1;
    bump2 = bump2 & 1;
    bump3 = bump3 & 1;
    bump4 = bump4 & 1;
    bump5 = bump5 & 1;

    return ( (bump0 << 0) + (bump1 << 1) + (bump2 << 2) + (bump3 << 3) + (bump4 << 4) + (bump5 << 5) ); //shift and sum

}


#define BUMP_INTERRUPT_PRIORITY 0
void (*BumpTask)(uint8_t bumpData); // function pointer for user task when bump interrupt is detected

// Initializes the bump switch pins and enables Port 4 GPIO interrupts
//This function sets up an interrupt on the Port4 bump switches.  There are a couple steps to initialize a hardware interrupt that is outlined in the lecture and is reproduced below.  Each step corresponds to a call to the driver library.

  //Initialize the Bump sensors
  //Using GPIO set event (edge)
  //Using GPIO clear flags
  //Using GPIO enable interrupt
  //Using NVIC enable interrupt
  //Using NVIC set the priority

void Bump_Interrupt_Init(void(*task)(uint8_t)){
    //Write this for Interrupt Module Race-Day
    // set BumpTask to be then user function to be called in ISR,
    BumpTask = task;

    // initialize bump pins as GPIO inputs with pull up resistors
    GPIO_setAsInputPinWithPullUpResistor(BUMP_PORT, BUMP_PINS);

    // configure falling edge interrupts on bump pins
    GPIO_interruptEdgeSelect(BUMP_PORT, BUMP_PINS, GPIO_HIGH_TO_LOW_TRANSITION);

    // clear interrupt flags on bump pins
    GPIO_clearInterruptFlag(BUMP_PORT, BUMP_PINS);

    // enable interrupts with GPIO on the bump pins
    GPIO_enableInterrupt(BUMP_PORT, BUMP_PINS);

    // enable the P4 interrupts in the NVIC
    Interrupt_enableInterrupt(INT_PORT4);

    // set the bump interrupts to the desired priority (remember to shift it to the corect location)
    Interrupt_setPriority(INT_PORT4, BUMP_INTERRUPT_PRIORITY);

}


// ISR for bump interrupts
// clear interrupt flag, read bump switches, and call user function for handling a collision
// there is only one line of code for you to add to this function, that is the call to the DL function 
// that clears the interrupt flag.
void PORT4_IRQHandler(void){
    uint8_t bumpData;
    //write this for Interrupt Module Race-Day
    // read bump switch data to be passed to the bump task
    bumpData = Bump_Read();
    GPIO_clearInterruptFlag(BUMP_PORT, BUMP_PINS);
    //bumpData = Bump_Read(); //Calls bump task

    // Call the bump task with the bumpData
    BumpTask(bumpData);

    // triggers interrupt calls toggle LED 2 seconds
    // if you don't clear it it cues up another interrupt, more of a bounce thing

    //clearing the flag before and after, anything inbetween, you clear first time, if there was an interrupt in the middle you would clear it at the end and you wouldn't really doing anything.

    // press bump switch, because debounce it sees multiple falling edges and it calls clear interupt flag twice.


    // clear interrupt flags
    GPIO_clearInterruptFlag(BUMP_PORT, BUMP_PINS);
    //BumpTask(bumpData); //This makes the light last an extra couple seconds longer

}
