/**
* @file slew.h
* @brief Contains the slew rate controller wrapper for the motors
* @author Chris Jerrett
* @date 9/14/17
**/
#pragma once

#include <API.h>
#include <math.h>
#include <stdlib.h>
#include "log.h"

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
#define RAMP_PROPORTION 2

/**
* @brief mutex to protect the data in the array of speeds from being read or written to simultaneusly.
* @author Chris Jerrett
* @date 9/14/17
**/
static Mutex mutex;

/**
* @brief Array of motor speed values to set the motors to.
* @author Chris Jerrett
* @date 9/14/17
**/
static signed char *motors_set_speeds = NULL;

/**
* @brief Task that will handle upadting the motors on a routine period.
* @author Chris Jerrett
* @date 9/14/17
**/
static TaskHandle slew = NULL; //TaskHandle is of type void*

/**
* @brief Boolean indicating whether or not the slew rate controller has been initialized
* @author Chris Jerrett
* @date 9/14/17
**/
static bool initialized = false;

/**
* @brief Closes the distance between the desired motor value and the current motor value by half for each motor
* @author Chris Jerrett
* @date 9/14/17
**/
static void updateMotors(){
  //Take back half approach
  //Not linear but equal to setSpeed(1-(1/2)^x)
  if(mutexTake(mutex, 100)) {
    for(int i = 0; i < MOTOR_PORTS; i++) {
      char set_speed = motors_set_speeds[i];
      char curr_speed = motorGet(i);
      char diff = set_speed - curr_speed;
      motorSet(i, curr_speed+ceil(diff/(float)RAMP_PROPORTION));
    }
    mutexGive(mutex);
  }
}
/**
* @brief Initializes the slew rate controller.
* @author Chris Jerrett, Christian DeSimone
* @date 9/14/17
**/
void initslew(){
  motors_set_speeds = (signed char*) calloc(MOTOR_PORTS, sizeof(signed char));
  mutex = mutexCreate();
  slew = taskRunLoop(updateMotors, UPDATE_PERIOD_MS);
  initialized = true;
}

/**
* @brief Deinitializes the slew rate controller and frees memory.
* @author Chris Jerrett
* @date 9/14/17
**/
void deinitslew(){
  free(motors_set_speeds);
  taskDelete(slew);
}
/**
* @brief Sets motor speed wrapped inside the slew rate controller
* @param motor the motor port to use
* @param speed the speed to use, between -127 and 127
* @author Chris Jerrett
*@date 9/14/17
**/
void setMotorS(int motor, int speed){
  if(mutexTake(mutex, 100)) {
      motors_set_speeds[motor] = speed;
      mutexGive(mutex);
  }
}
