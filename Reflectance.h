/**
 * @file      Reflectance.h
 * @brief     Provides low-level functions for interfacing with Reflectance sensors
 ******************************************************************************/


/*
 * Reflectance.h
 * Provides function definitions to
 * 1. Initialize Pololu reflectance sensor
 * 2. Read Pololu reflectance sensor
 * 3. Determine robot position
 * 4. Determine robot status
 *
 */
#ifndef REFLECTANCE_H_
#define REFLECTANCE_H_


#define ON_LINE 3
#define LEFT    2
#define RIGHT   1
#define LOST    0

/**
 * Initialize reflectance sensor
 * LED Output: P5.3
 * Sensor 1-8 (right to left) P7.0 - P7.7
 * @param none
 * @return none
 */
void Reflectance_Init(void);

/**
 * Read reflectance sensor
 * @param time the delay time in us
 * @return result the sensor readings, bit 0 corresponds to the rightmost sensor, bit 7 to the leftmost sensor
 */
uint8_t Reflectance_Read(uint32_t time);

/**Determine robot status over the line
 * @param time the delay time is us
 * @return result the robot location status (LOST/RIGHT/LEFT/ON LINE)
 */
uint8_t Reflectance_Center(uint32_t time);


/**
 * Determine the robot position
 * @param data the collected sensor data
 * @return result the postion value between +345 (most left) to -345 (most right)
 */
int32_t Reflectance_Position(uint8_t data);

/*
 * Start collecting reflectance sensor data by turning on the LEDs, charging the capacitors, waiting,
 * and then set the sensor pins as input
 * @param none
 * @return none
 */
void Reflectance_Start(void);

/* Finish collecting reflectance sensor data by reading the result from the P7 input register and turning off the LEDs
 * @param none
 * @return result the sensor data
 */
uint8_t Reflectance_End(void);


#endif /* REFLECTANCE_H_ */
