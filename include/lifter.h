#ifndef _LIFTER_H_
#define _LIFTER_H_

#include <API.h>
#include "motor_ports.h"
#include "slew.h"
#include "controller.h"

void set_lifter_motors(const char);

void set_lifter_pos(int pos);

void update_lifter();

#endif
