#ifndef _GOAL_H_
#define _GOAL_H_

#include "slew.h"
#include <API.h>
#include "controller.h"
#include "motor_ports.h"

void raise_goal();
void lower_goal();
void update_goal();

#endif
