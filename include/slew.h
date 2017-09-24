/**
* @file slew.h
* @brief Contains the slew rate controller wrapper for the motors
* @author Chris Jerrett
* @date 9/14/17
**/

#ifndef _SLEW_H_
#define _SLEW_H_

#include <API.h>
#include <math.h>
#include <vlib.h>

/**
* @brief How frequently to update the motors, in milliseconds
* @author Chris Jerrett
* @date 9/14/17
**/
#define UPDATE_PERIOD_MS 25

/**
* @brief The number of motor ports on the robot
* @author Christian DeSimone
* @date 9/14/17
**/
#define MOTOR_PORTS 12

/**
* @brief proportion defining how quickly the motor should converge on the correct value. higher value leads to slower convergence
* @author Chris Jerrett
* @date 9/14/17
**/
#define RAMP_PROPORTION 1

/**
* @brief Closes the distance between the desired motor value and the current motor value by half for each motor
* @author Chris Jerrett
* @date 9/14/17
**/
void updateMotors();

/**
* @brief Deinitializes the slew rate controller and frees memory.
* @author Chris Jerrett
* @date 9/14/17
**/
void deinitslew();

/**
* @brief Initializes the slew rate controller.
* @author Chris Jerrett, Christian DeSimone
* @date 9/14/17
**/
void init_slew();

/**
* @brief Sets motor speed wrapped inside the slew rate controller
* @param motor the motor port to use
* @param speed the speed to use, between -127 and 127
* @author Chris Jerrett
*@date 9/14/17
**/
void set_motor_slew(int motor, char speed);

#endif
