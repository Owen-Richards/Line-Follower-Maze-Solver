// built-in LED1 connected to P1.0
// negative logic built-in Button 1 connected to P1.1
// negative logic built-in Button 2 connected to P1.4
// built-in red LED connected to P2.0
// built-in green LED connected to P2.1
// built-in blue LED connected to P2.2

#include "driverlib.h"

#include "gpio.h"
#include "LaunchPad.h"

//------------LaunchPad_Init------------
// Initialize Switch input and LED output
// Input: none
// Output: none


void LaunchPad_Init(void){
  // setup bump switches as input with pull up resistor
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN4);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);

  // set the red led 1.0 as output and set it low
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);


  // set RGB pins as output with high drive strength and set them all low
  // pins are 2.0-2.2
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN1 );
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN2);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0 );
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1 );
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2 );
    GPIO_setDriveStrengthHigh(GPIO_PORT_P2, GPIO_PIN0 );
    GPIO_setDriveStrengthHigh(GPIO_PORT_P2, GPIO_PIN1);
    GPIO_setDriveStrengthHigh(GPIO_PORT_P2, GPIO_PIN2);
}


//------------LaunchPad_Input------------
// Input from Switches 
// Input: none
// Output: 0x00 none
//         0x01 Button1
//         0x02 Button2
//         0x03 both Button1 and Button2
uint8_t LaunchPad_Input(void){
  // read pin P1.1 [000000X0] and pin P1.4 [000X0000]
    uint_fast8_t port1 = GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1);
    uint_fast8_t port4= GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN4);
  // use bit-shifting to return appropriate output
    return ((~port1 & 1) | ((~port4 & 1) << 1));
}

//------------LaunchPad_LED------------
// Output to LaunchPad red LED
// Input: 0 off, 1 on
// Output: none
void LaunchPad_LED(uint8_t data){  
    // set P1.0 as either high or low, according to
    // the value in data
  if (data){
      GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0 );
  }
  else {
      GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
  }
}

//------------LaunchPad_Output------------
// Output to LaunchPad LEDs 
// Input: 0 off, bit0=red,bit1=green,bit2=blue
// Output: none
void LaunchPad_Output(uint8_t data){  
  // write three bits (data) to the appropriate
  // pins (0,1,2) on port 2
  if ( data & 0x01 ){
      GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);
  }
  else {
      GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0);
  }
  if ( (data & 0x02) >> 1 ){
      GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1);
  }
  else {
       GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1);
   }
  if ( (data & 0x04) >> 2 ){
      GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN2);
  }
  else {
       GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2);
   }
}
