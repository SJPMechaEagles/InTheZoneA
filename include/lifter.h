#ifndef _LIFTER_H_
#define _LIFTER_H_

#include <API.h>
#include "motor_ports.h"
#include "sensor_ports.h"
#include "slew.h"
#include "controller.h"
#include "potentiometer.h"

#define TICK_DIFF 680

#define LIFTER_P .2
#define LIFTER_D .00
#define LIFTER_I 0


#define LENGTH_LONG 13.5
#define HEIGHT 19.1 - 3.8
#define LENGTH_SHORT 10.5

#define LIFTER_UP MASTER, RIGHT_BUTTONS, JOY_UP
#define LIFTER_DOWN MASTER, RIGHT_BUTTONS, JOY_DOWN

#define LIFTER_UP_PARTNER PARTNER, RIGHT_BUTTONS, JOY_UP
#define LIFTER_DOWN_PARTNER PARTNER, RIGHT_BUTTONS, JOY_DOWN

void set_lifter_motors(const int);

void set_lifter_pos(int pos);

void update_lifter();

float lifterPotentiometerToDegree(int x);

double getLifterHeight();

int getLifterTicks();

#endif
