#ifndef _MOBILE_GOAL_H_
#define _MOBILE_GOAL_H_

#include "controller.h"
#include "motor_ports.h"
#include "slew.h"

#define MOBILE_GOAL_UP 1218
#define MOBILE_GOAL_DOWN 4020
#define MOBILE_GOAL_POT_PORT 1


void mobile_goal_down_pot(void *param);

void mobile_goal_up_pot(void *param);


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
void inline raise_intake();

/**
 * @brief lowers the intake
 **/
void inline lower_intake();

#endif
