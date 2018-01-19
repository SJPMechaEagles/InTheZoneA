/**
 * @file lifter.h
 * @author Chris Jerrett, Christian Desimone
 * @date 8/27/2017
 * @brief Declarations and macros for controlling and manipulating the lifter.
 **/
#ifndef _LIFTER_H_
#define _LIFTER_H_

#include "controller.h"
#include "drive.h"
#include "motor_ports.h"
#include "potentiometer.h"
#include "sensors.h"
#include "slew.h"
#include <API.h>

/**
 * @brief The initial rotation of the lifter potentiometer at height zero
 **/
#define INIT_ROTATION 680

/**
 * @brief The proportional constant for the secondary lifter PID
 **/
#define SECONDARY_LIFTER_P .05

/**
 * @brief The derivative constant for the secondary lifter PID
 **/
#define SECONDARY_LIFTER_D 0

/**
 * @brief The integral constant for the secondary lifter PID
 **/
#define SECONDARY_LIFTER_I 0.000

/**
 * @brief The proportional constant for the main lifter PID
 **/
#define MAIN_LIFTER_P 0

/**
 * @brief The derivative constant for the main lifter PID
 **/
#define MAIN_LIFTER_D 0

/**
 * @brief The integral constant for the main lifter PID
 **/
#define MAIN_LIFTER_I 0.0000001

/**
 * @brief The threshold of a signficant speed for the lifter
 **/
#define THRESHOLD 10

/**
 * @brief The integral constant for the lifter PID
 **/
#define HEIGHT 19.1 - 3.8

/**
 * @brief The lifter up controller params
 **/
#define LIFTER_UP PARTNER, 6, JOY_UP

/**
 * @brief The lifter down controller params
 **/
#define LIFTER_DOWN PARTNER, 6, JOY_DOWN

/**
 * @brief The secondary lifter up controller params
 **/
#define SECONDARY_LIFTER_UP PARTNER, 5, JOY_UP

/**
 * @brief The secondary lifter down controller params
 **/
#define SECONDARY_LIFTER_DOWN PARTNER, 5, JOY_DOWN

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
 * @brief The port the secondary lifter potenteometer is plugged into.
 **/
#define SECONDARY_LIFTER_POT_PORT 2

/**
 * @brief Max potentiomenter value for secondary lifter.
 **/
#define SECONDARY_LIFTER_MAX_HEIGHT 3120

/**
 * @brief Min potentiomenter value for secondary lifter.
 */
#define SECONDARY_LIFTER_MIN_HEIGHT 2000

/**
 * @brief The port the main lifter potentemometer is plugged into.
 **/
#define MAIN_LIFTER_POT 1

/**
 * @brief The port the main lifter potentemometer is plugged into.
 **/
#define MAIN_LIFTER_MIN_HEIGHT 1700

/**
 * @brief Sets the secondary lifter motors to the given value
 *
 * @param v value for the lifter motor. Between -128 - 127, any values outside
 *are clamped.
 * @author Chris Jerrett
 * @date 1/6/2018
 **/
void set_secondary_lifter_motors(const int v);

/**
 * @brief Sets the main lifter motors to the given value
 *
 * @param v value for the lifter motor. Between -128 - 127, any values outside
 *are clamped.
 * @author Chris Jerrett
 * @date 9/9/2017
 **/
void set_main_lifter_motors(const int v);

/**
 * @brief Sets the lifter positions to the given value
 *
 * @param pos The height in inches
 * @author Chris Jerrett
 * @date 9/12/2017
 **/
void set_lifter_pos(int pos);

/**
 * @brief Raises the main lifter
 *
 * @author Christian DeSimone
 * @date 9/12/2017
 **/
void raise_main_lifter();

/**
 * @brief Lowers the main lifter
 *
 * @author Christian DeSimone
 * @date 9/12/2017
 **/
void lower_main_lifter();

/**
 * @brief Raises the main lifter
 *
 * @author Christian DeSimone
 * @date 9/12/2017
 **/
void raise_secondary_lifter();

/**
 * @brief Lowers the secondary lifter
 *
 * @author Christian DeSimone
 * @date 9/12/2017
 **/
void lower_secondary_lifter();

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
 * @brief Gets the value of the lifter pot.
 *
 * @return the value of the pot.
 * @author Chris Jerrett
 * @date 9/9/2017
 **/
int getLifterTicks();

/**
 * @brief Gets the height of the lifter in inches.
 *
 * @return the height of the lifter.
 * @author Chris Jerrett
 * @date 9/17/2017
 **/
double getLifterHeight();

/**
 * Autostacks a cone once picked up
 * @param param ignored parameter
 */
void autostack_routine(void *param);

/**
 * Stpos an autostack in case of an error
 * @param param ignore parameter
 */
void interrupt_auto_stack(void *param);

#endif
