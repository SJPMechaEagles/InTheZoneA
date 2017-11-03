#ifndef _CLAW_H_
#define _CLAW_H_

#include "slew.h"
#include <API.h>
#include "controller.h"
#include "motor_ports.h"

void update_claw();
void set_claw_motor(const char v);
int getClawTicks();
void open_claw();
void close_claw();

#endif
