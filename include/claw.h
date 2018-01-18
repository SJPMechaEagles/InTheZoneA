/**
 * @file claw.h
 * @author Chris Jerrett, Christian Desimone
 * @date 8/30/2017
 * @brief Code for controlling the claw that grabs the cones
 **/
#ifndef _CLAW_H_
#define _CLAW_H_

#include "controller.h"
#include "motor_ports.h"
#include "sensor_ports.h"
#include "slew.h"
#include <API.h>

/**
 * @brief The max motor vlaue of the claw.
 * @author Chris Jerrett
 **/
#define MAX_CLAW_SPEED 127
/**
 * @brief The min motor vlaue of the claw.
 * @author Chris Jerrett
 **/
#define MIN_CLAW_SPEED -127

/**
 * @brief The joystick parameters for closing the claw
 * @author Chris Jerrett
 **/
#define CLAW_CLOSE PARTNER, 8, JOY_DOWN

/**
 * @brief The joystick parameters for opening the claw
 * @author Chris Jerrett
 **/
#define CLAW_OPEN PARTNER, 8, JOY_RIGHT

/**
 * @brief The potentiometer value for a closed claw
 * @author Chris Jerrett
 **/
#define CLAW_CLOSE_VAL 3000

/**
 * @brief The potentiometer value for a open claw
 * @author Chris Jerrett
 **/
#define CLAW_OPEN_VAL 1500

/**
 * @brief Updates the claw motor values
 * @author Chris Jerrett
 **/
void update_claw();

/**
 * @brief sets the claw motor speed
 * @author Chris Jerrett
 **/
void set_claw_motor(const int v);

/**
 * @brief Gets the claw position in potentiometer ticks
 * @author Chris Jerrett
 **/
unsigned int getClawTicks();

/**
 * @brief Drives the motors to open the claw
 * @author Chris Jerrett
 **/
void open_claw();

/**
 * @brief Drives the motors to close the claw
 * @author Chris Jerrett
 **/
void close_claw();

/**
 * @brief The different states of the claw
 * @author Chris Jerrett
 **/
enum claw_state { CLAW_OPEN_STATE, CLAW_CLOSE_STATE, CLAW_NEUTRAL_STATE };

#endif
