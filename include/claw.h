#ifndef _CLAW_H_
#define _CLAW_H_

#include "slew.h"
#include <API.h>
#include "controller.h"
#include "motor_ports.h"
#include "sensor_ports.h"

/**
* @brief The proportional constant for the claw PID controller.
* @author Chris Jerrett
**/
#define CLAW_P .1
/**
* @brief The derivative constant for the claw PID controller.
* @author Chris Jerrett
**/
#define CLAW_D .1
/**
* @brief The integral constant for the claw PID controller.
* @author Chris Jerrett
**/
#define CLAW_I 0

/**
* @brief The max motor vlaue of the claw.
* @author Chris Jerrett
**/
#define MAX_CLAW_SPEED 50
/**
* @brief The min motor vlaue of the claw.
* @author Chris Jerrett
**/
#define MIN_CLAW_SPEED -50

/**
* @brief The joystick parameters for closing the claw
* @author Chris Jerrett
**/
#define CLAW_CLOSE MASTER, 6, JOY_UP

/**
* @brief The joystick parameters for opening the claw
* @author Chris Jerrett
**/
#define CLAW_OPEN MASTER, 6, JOY_DOWN

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
enum claw_state {
  CLAW_OPEN_STATE,
  CLAW_CLOSE_STATE
};

#endif
