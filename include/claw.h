#ifndef _CLAW_H_
#define _CLAW_H_

#include "slew.h"
#include <API.h>
#include "controller.h"
#include "motor_ports.h"
#include "sensor_ports.h"

#define CLAW_P .10
#define CLAW_D .00
#define CLAW_I .004
#define MAX_CLAW_SPEED 70
#define MIN_CLAW_SPEED -70

#define CLAW_CLOSE MASTER, RIGHT_BUTTONS, JOY_LEFT
#define CLAW_OPEN MASTER, RIGHT_BUTTONS, JOY_RIGHT

enum claw_state {
  open,
  close
};

void update_claw();
void set_claw_motor(const char v);
unsigned int getClawTicks();
void open_claw();
void close_claw();

#endif
