#include <stdint.h>
/*
 * Reflectance.c
 * Provides functions to
 * 1. Initialize Pololu reflectance sensor
 * 2. Read Pololu reflectance sensor
 * 3. Determine robot position
 * 4. Determine robot status
 *
 */

#include "driverlib.h"
#include "gpio.h"
#include "Clock.h"
#include "Reflectance.h"

#define ALLBITS  0xFF
#define BITSHIFT 0x01

//------------Reflectance_Init------------
// Initialize sensor array to GPIO, set LEDs (P5.3 and P9.2) 
// as output and sensors (P7.0-P7.7) as output
// Input: none
// Output: none
void Reflectance_Init(void){

    GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_PIN3);
    GPIO_setAsOutputPin(GPIO_PORT_P9, GPIO_PIN2);

    GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN3);
    GPIO_setOutputLowOnPin(GPIO_PORT_P9, GPIO_PIN2);

    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN1);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN2);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN3);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN4);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN5);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN6);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN7);
}


//------------Reflectance_Read------------
// Read reflectance sensor
// Input: the delay time in us
// Output: result the sensor readings, bit 0 corresponds 
//         to the rightmost sensor, bit 7 to the leftmost sensor
uint8_t Reflectance_Read(uint32_t time){

    //Set P5.3 and P9.2 high (turn on the IR LED)
    GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN3);
    GPIO_setOutputHighOnPin(GPIO_PORT_P9, GPIO_PIN2);

    //Set P7.0 - P7.7 as output and set to high (charging 8 capacitors)
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN1);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN2);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN3);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN4);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN5);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN6);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN7);

    GPIO_setOutputHighOnPin(GPIO_PORT_P7, GPIO_PIN0);
    GPIO_setOutputHighOnPin(GPIO_PORT_P7, GPIO_PIN1);
    GPIO_setOutputHighOnPin(GPIO_PORT_P7, GPIO_PIN2);
    GPIO_setOutputHighOnPin(GPIO_PORT_P7, GPIO_PIN3);
    GPIO_setOutputHighOnPin(GPIO_PORT_P7, GPIO_PIN4);
    GPIO_setOutputHighOnPin(GPIO_PORT_P7, GPIO_PIN5);
    GPIO_setOutputHighOnPin(GPIO_PORT_P7, GPIO_PIN6);
    GPIO_setOutputHighOnPin(GPIO_PORT_P7, GPIO_PIN7);
    //Wait 10 us, Clock_Delay1us(10)

    Clock_Delay1us(10);
    //Set P7.0 - P7.7 as input

    GPIO_setAsInputPin(GPIO_PORT_P7, GPIO_PIN0);
    GPIO_setAsInputPin(GPIO_PORT_P7, GPIO_PIN1);
    GPIO_setAsInputPin(GPIO_PORT_P7, GPIO_PIN2);
    GPIO_setAsInputPin(GPIO_PORT_P7, GPIO_PIN3);
    GPIO_setAsInputPin(GPIO_PORT_P7, GPIO_PIN4);
    GPIO_setAsInputPin(GPIO_PORT_P7, GPIO_PIN5);
    GPIO_setAsInputPin(GPIO_PORT_P7, GPIO_PIN6);
    GPIO_setAsInputPin(GPIO_PORT_P7, GPIO_PIN7);

    //Wait time us, Clock_Delay1us(time)
    Clock_Delay1us(time);
    //Read P7.7 - P7.0 inputs
    uint8_t Por0 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN0);
    uint8_t Por1 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN1);
    uint8_t Por2 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN2);
    uint8_t Por3 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN3);
    uint8_t Por4 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN4);
    uint8_t Por5 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN5);
    uint8_t Por6 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN6);
    uint8_t Por7 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN7);

    //Set P5.3 and P9.2 low (turn off IR LED)
    GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN3);
    GPIO_setOutputLowOnPin(GPIO_PORT_P9, GPIO_PIN2);

    //Return 8-bit binary value read from P7.7 - P7
   Por0 = Por0;
   Por1 = Por1 << 1;
   Por2 = Por2 << 2;
   Por3 = Por3 << 3;
   Por4 = Por4 << 4;
   Por5 = Por5 << 5;
   Por6 = Por6 << 6;
   Por7 = Por7 << 7;

   uint8_t Pall;
   Pall = Por0 + Por1 + Por2 + Por3 + Por4 + Por5 + Por6 + Por7;
    return Pall;
            //P7 -> IN;
}

void Reflectance_Start(void){

    //Set P5.3 and P9.2 high (turn on the IR LED)
    GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN3);
    GPIO_setOutputHighOnPin(GPIO_PORT_P9, GPIO_PIN2);

    //Set P7.0 - P7.7 as output and set to high (charging 8 capacitors)
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN1);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN2);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN3);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN4);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN5);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN6);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN7);

    GPIO_setOutputHighOnPin(GPIO_PORT_P7, GPIO_PIN0);
    GPIO_setOutputHighOnPin(GPIO_PORT_P7, GPIO_PIN1);
    GPIO_setOutputHighOnPin(GPIO_PORT_P7, GPIO_PIN2);
    GPIO_setOutputHighOnPin(GPIO_PORT_P7, GPIO_PIN3);
    GPIO_setOutputHighOnPin(GPIO_PORT_P7, GPIO_PIN4);
    GPIO_setOutputHighOnPin(GPIO_PORT_P7, GPIO_PIN5);
    GPIO_setOutputHighOnPin(GPIO_PORT_P7, GPIO_PIN6);
    GPIO_setOutputHighOnPin(GPIO_PORT_P7, GPIO_PIN7);
    //Wait 10 us, Clock_Delay1us(10)

    Clock_Delay1us(10);
    //Set P7.0 - P7.7 as input

    GPIO_setAsInputPin(GPIO_PORT_P7, GPIO_PIN0);
    GPIO_setAsInputPin(GPIO_PORT_P7, GPIO_PIN1);
    GPIO_setAsInputPin(GPIO_PORT_P7, GPIO_PIN2);
    GPIO_setAsInputPin(GPIO_PORT_P7, GPIO_PIN3);
    GPIO_setAsInputPin(GPIO_PORT_P7, GPIO_PIN4);
    GPIO_setAsInputPin(GPIO_PORT_P7, GPIO_PIN5);
    GPIO_setAsInputPin(GPIO_PORT_P7, GPIO_PIN6);
    GPIO_setAsInputPin(GPIO_PORT_P7, GPIO_PIN7);

}

uint8_t Reflectance_End(void){
    uint8_t Por0 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN0);
        uint8_t Por1 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN1);
        uint8_t Por2 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN2);
        uint8_t Por3 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN3);
        uint8_t Por4 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN4);
        uint8_t Por5 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN5);
        uint8_t Por6 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN6);
        uint8_t Por7 = GPIO_getInputPinValue(GPIO_PORT_P7, GPIO_PIN7);

        //Set P5.3 and P9.2 low (turn off IR LED)
        GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN3);
        GPIO_setOutputLowOnPin(GPIO_PORT_P9, GPIO_PIN2);

        //Return 8-bit binary value read from P7.7 - P7
       Por0 = Por0;
       Por1 = Por1 << 1;
       Por2 = Por2 << 2;
       Por3 = Por3 << 3;
       Por4 = Por4 << 4;
       Por5 = Por5 << 5;
       Por6 = Por6 << 6;
       Por7 = Por7 << 7;

       uint8_t Pall;
       return Pall = Por0 + Por1 + Por2 + Por3 + Por4 + Por5 + Por6 + Por7;
        //return Pall;

//        uint8_t data = Pall;
//        int32_t W_i[8] = {334, 238, 142, 48, -48, -142, -238, -334};
//
//            //Define b_i to be 0 (white) or 1 (black) for each binary bit in data
//
//            int32_t b_i[8];
//            int i;
//            uint8_t copydata = data;
//            for (i=7; i >= 0; i--){
//                b_i[i] = (copydata & 0x01);
//                copydata = copydata >> 1;
//            }
//
//            int32_t sumb_i = 0;
//            int32_t sumW_i = 0;
//
//            for (i = 0; i < 8; i++){
//                sumb_i += b_i[i];
//                sumW_i += b_i[i]*W_i[i];
//            }
//
//            if (sumb_i == 0 ){
//                return 1000;
//            }
//
//            int32_t distance = (sumW_i/sumb_i);
//            return distance;

//        //Using bit masking, create a variable to be the middle-left sensor and mask it appropriately
//
//        uint8_t mid_left = (linesensor & 0x08) >> 3;
//
//        //Create a variable to be the middle-right sensor and mask it appropriately
//
//        uint8_t mid_right = (linesensor & 0x10) >> 4;
//
//        //Use a series of if statements to determine the robot’s position
//        if (mid_left == 1 && mid_right == 1){
//           return 3;
//        }
//        else if (mid_left == 1 && mid_right == 0){
//            return 2;
//        }
//        else if (mid_left == 0 && mid_right == 1){
//            return 1;
//        }
//        return 0;
                //P7 -> IN;
}

//------------Reflectance_Center------------
// Determine robot's status over the line
// Input: the delay time in us
// Output: result the robot location status (LOST/RIGHT/LEFT/ON LINE)
uint8_t Reflectance_Center(uint32_t time){
    //Get reflectance read data
    //Get value from left center sensor
    //Get value from right center sensor
    
    /* Check robot status truth table
     * INPUT (L,R) | OUTPUT
     * ------------|------------
     *      11     | ON_LINE (3)
     *      10     | LEFT    (2)
     *      01     | RIGHT   (1)
     *      00     | LOST    (0)
     */
    //uint8_t lineSensor =
    //Read the line sensor using Reflectance_Read(time)
    uint8_t linesensor = Reflectance_Read(time);

    //Using bit masking, create a variable to be the middle-left sensor and mask it appropriately

    uint8_t mid_left = (linesensor & 0x08) >> 3;

    //Create a variable to be the middle-right sensor and mask it appropriately

    uint8_t mid_right = (linesensor & 0x10) >> 4;

    //Use a series of if statements to determine the robot’s position
    if (mid_left == 1 && mid_right == 1){
       return 3;
    }
    else if (mid_left == 1 && mid_right == 0){
        return 2;
    }
    else if (mid_left == 0 && mid_right == 1){
        return 1;
    }
    return 0;

}

//------------Reflectance_Position------------
// Determine robot's status over the line
// Input: the collected sensor data 
// Output: the position value between +345 (most left)
//         to -345 (most right)
int32_t Reflectance_Position(uint8_t data){

    //Define a weight vector, W_i = {334, 238, 142, 48, -48, -142, -238, -334}
    int32_t W_i[8] = {334, 238, 142, 48, -48, -142, -238, -334};

    //Define b_i to be 0 (white) or 1 (black) for each binary bit in data

    int32_t b_i[8];
    int i;
    uint8_t copydata = data;
    for (i=7; i >= 0; i--){
        b_i[i] = (copydata & 0x01);
        copydata = copydata >> 1;
    }

    int32_t sumb_i = 0;
    int32_t sumW_i = 0;

    for (i = 0; i < 8; i++){
        sumb_i += b_i[i];
        sumW_i += b_i[i]*W_i[i];
    }

    if (sumb_i == 0 ){
        return 1000;
    }

    int32_t distance = (sumW_i/sumb_i);
    return distance;
}

