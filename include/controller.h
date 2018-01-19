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
 * @brief renames the controller inputs. Allows more readable controls.
 * @author Chris Jerrett
 * @date 12/18/17
 */
typedef enum {
  JOY1_5D = 0,
  JOY1_5U = 1,
  JOY1_6D = 2,
  JOY1_6U = 3,
  JOY1_7U = 4,
  JOY1_7L = 5,
  JOY1_7R = 6,
  JOY1_7D = 7,
  JOY1_8U = 8,
  JOY1_8L = 9,
  JOY1_8R = 10,
  JOY1_8D = 11,

  JOY2_5D = 12,
  JOY2_5U = 13,
  JOY2_6D = 14,
  JOY2_6U = 15,
  JOY2_7U = 16,
  JOY2_7L = 17,
  JOY2_7R = 18,
  JOY2_7D = 19,
  JOY2_8U = 20,
  JOY2_8L = 21,
  JOY2_8R = 22,
  JOY2_8D = 23,

  LCD_LEFT = 24,
  LCD_CENT = 25,
  LCD_RIGHT = 26
} button_t;

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
