#ifndef _LIFTER_H_
#define _LIFTER_H_

#define LENGTH_LONG (13.5)
#define HEIGHT (19.1 - 3.8)
#define LENGTH_SHORT (10.5)

#include <API.h>
#include "motor_ports.h"
#include "slew.h"
#include "controller.h"

void set_lifter_motors(const char);

void set_lifter_pos(int pos);

void update_lifter();

float lifterPotentiometerToDegree(int x);

double getLifterHeight();

int getLifterTicks();

#endif
