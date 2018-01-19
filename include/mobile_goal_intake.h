#ifndef _MOBLE_GOAL_INTAKE_
#define _MOBLE_GOAL_INTAKE_

#include "controller.h"
#include "motor_ports.h"
#include "slew.h"

/**
 * @brief updates the mobile goal intake in teleop.
 *
 * @author Chris Jerrett
 */
void update_intake();

/**
 * @brief sets the intake motor
 * @author Chris Jerrett
 **/
void set_intake_motor(int n);

/**
 * @brief raises the intake
 **/
void raise_intake();

/**
 * @brief lowers the intake
 **/
void lower_intake();

#endif
