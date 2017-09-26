#include "claw.h"

void update_claw() {
  if(joystickGetDigital(MASTER, 8, JOY_RIGHT)) {
    close_claw();
  }
  else if(joystickGetDigital(MASTER, 8, JOY_LEFT)) {
    open_claw();
  }else {
    set_motor_slew(CLAW_MOTOR, 0);
  }
}

void open_claw() {
  motorSet(CLAW_MOTOR, 50);
}

void close_claw() {
  motorSet(CLAW_MOTOR, -50);
}
