/**
* @file lifter.h
* @author Chris Jerrett, Christian Desimone
* @date 8/27/2017
* @brief Declarations and macros for controlling and manipulating the lifter.
**/
#ifndef _LIFTER_H_
#define _LIFTER_H_

#include <API.h>
#include "motor_ports.h"
#include "sensor_ports.h"
#include "slew.h"
#include "controller.h"
#include "potentiometer.h"
#include "partner.h"
#include "drive.h"

/**
* @brief The initial rotation of the lifter potentiometer at height zero
**/
#define INIT_ROTATION 680

/**
* @brief The proportional constant for the lifter PID
**/
#define LIFTER_P .15

/**
* @brief The derivative constant for the lifter PID
**/
#define LIFTER_D 0

/**
* @brief The threshold of a signficant speed for the lifter
**/
#define THRESHOLD 10

/**
* @brief The integral constant for the lifter PID
**/
#define LIFTER_I 0


/**
* @brief The integral constant for the lifter PID
**/
#define HEIGHT 19.1 - 3.8

/**
* @brief The lifter up controller params
**/
#define LIFTER_UP MASTER, 5, JOY_UP

/**
* @brief The lifter down controller params
**/
#define LIFTER_DOWN MASTER, 5, JOY_DOWN

/**
* @brief Height to raise lifter to driver preload height
**/
#define LIFTER_DRIVER_LOAD MASTER, RIGHT_BUTTONS, JOY_RIGHT

/**
* @brief The lifter up controller params for the partner
**/
#define LIFTER_UP_PARTNER PARTNER, 5, JOY_UP

/**
* @brief The lifter down controller params for the partner
**/
#define LIFTER_DOWN_PARTNER PARTNER, 5, JOY_DOWN

/**
* @brief Sets the lifter motors to the given value
*
* @param v value for the lifter motor. Between -128 - 127, any values outside are clamped.
* @author Chris Jerrett
* @date 9/9/2017
**/
void set_lifter_motors(const int);

/**
* @brief Sets the lifter positions to the given value
*
* @param pos The height in inches
* @author Chris Jerrett
* @date 9/12/2017
**/
void set_lifter_pos(int pos);

/**
* @brief Updates the lifter in teleop.
*
* @author Chris Jerrett
* @date 9/9/2017
**/
void update_lifter();

/**
* @brief height of the lifter in degrees from 0 height
*
* @param x the pot value
* @return the positions in degrees
* @author Chris Jerrett
* @date 10/13/2017
**/
float lifterPotentiometerToDegree(int x);

/**
* @brief Gets the height of the lifter in inches.
*
* @return the height of the lifter.
* @author Chris Jerrett
* @date 9/17/2017
**/
double getLifterHeight();

/**
* @brief Gets the value of the lifter pot.
*
* @return the value of the pot.
* @author Chris Jerrett
* @date 9/9/2017
**/
int getLifterTicks();

#endif
