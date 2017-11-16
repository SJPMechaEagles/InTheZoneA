#ifndef _CLAW_H_
#define _CLAW_H_

#include "slew.h"
#include <API.h>
#include "controller.h"
#include "motor_ports.h"
#include "sensor_ports.h"

#define CLAW_P .08
#define CLAW_D .1
#define CLAW_I 0
#define MAX_CLAW_SPEED 50
#define MIN_CLAW_SPEED -50

#define CLAW_CLOSE MASTER, 6, JOY_UP
#define CLAW_OPEN MASTER, 6, JOY_DOWN

#define CLAW_CLOSE_VAL 2900
#define CLAW_OPEN_VAL 1500

void update_claw();
void set_claw_motor(const int v);
unsigned int getClawTicks();
void open_claw();
void close_claw();

enum claw_state {
  CLAW_OPEN_STATE,
  CLAW_CLOSE_STATE
};

#endif
