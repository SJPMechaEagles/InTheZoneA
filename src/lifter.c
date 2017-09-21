#include "lifter.h"

void set_lifter_motors(const char v) {
  set_motor_slew(MOTOR_LIFT_BOTTOM_RIGHT, v);
  set_motor_slew(MOTOR_LIFT_BOTTOM_LEFT, -v);
  set_motor_slew(MOTOR_LIFT_TOP_RIGHT, v);
  set_motor_slew(MOTOR_LIFT_TOP_LEFT, -v);
}

void set_lifter_pos(int pos) {}
