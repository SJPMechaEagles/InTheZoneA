#ifndef _CLAW_H_
#define _CLAW_H_

#include "slew.h"
#include <API.h>
#include "controller.h"
#include "motor_ports.h"
#include "sensor_ports.h"

#define CLAW_P .35
#define CLAW_D .3
#define CLAW_I .002
#define MAX_CLAW_SPEED 70
#define MIN_CLAW_SPEED -70

#define CLAW_CLOSE MASTER, RIGHT_BUTTONS, JOY_LEFT
#define CLAW_OPEN MASTER, RIGHT_BUTTONS, JOY_RIGHT

#define CLAW_CLOSE_VAL 1027
#define CLAW_OPEN_VAL 0

enum claw_state {
  open,
  close
};

void update_claw();
void set_claw_motor(const int v);
unsigned int getClawTicks();
void open_claw();
void close_claw();

#endif
