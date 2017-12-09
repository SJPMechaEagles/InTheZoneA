/**
* @file controller.h
* @author Chris Jerrett, Christian Desimone
* @date 9/9/2017
* @brief controller definitions, macros and functions to assist with usig the
* vex controllers.
**/

#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "vmath.h"
#include <API.h>

#define RIGHT_BUTTONS 8
#define LEFT_BUTTONS 7
#define RIGHT_BUMPERS 5
#define LEFT_BUMPERS 6

/**
* @brief the master controller
* @date 9/1/2017
* @author Chris Jerrett
**/
#define MASTER 1

/**
* @brief the slave/partner controller
* @date 9/1/2017
* @author Chris Jerrett
**/
#define PARTNER 2

/**
* @brief the right x joystick on controller
* @date 9/1/2017
* @author Chris Jerrett
**/
#define RIGHT_JOY_X 1

/**
* @brief the right y joystick on controller
* @date 9/1/2017
* @author Chris Jerrett
**/
#define RIGHT_JOY_Y 2

/**
* @brief the left x joystick on controller
* @date 9/1/2017
* @author Chris Jerrett
**/
#define LEFT_JOY_X 4

/**
* @brief the left y joystick on controller
* @date 9/1/2017
* @author Chris Jerrett
**/
#define LEFT_JOY_Y 3

/**
* @brief Represents a joystick on the controller
* @date 9/10/2017
* @author Chris Jerrett
**/
enum joystick {
  /** The right joystick **/
  RIGHT_JOY,
  /** The left joystick **/
  LEFT_JOY,
};

/**
* @brief Gets the location of a joystick on the controller
* @author Chris Jerrett
**/
struct cord get_joystick_cord(enum joystick side, int controller);

#endif
