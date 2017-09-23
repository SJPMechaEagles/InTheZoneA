#include "lifter.h"

void set_lifter_motors(const char v) {
  set_motor_slew(MOTOR_LIFT_BOTTOM_RIGHT, v);
  set_motor_slew(MOTOR_LIFT_BOTTOM_LEFT, -v);
  set_motor_slew(MOTOR_LIFT_TOP_RIGHT, v);
  set_motor_slew(MOTOR_LIFT_TOP_LEFT, -v);
}

void set_lifter_pos(int pos) {

}

void raise_lifter(){
  set_lifter_motors(127);
}

void lower_lifter(){
  set_lifter_motors(-127);
}

void update_lifter() {
  if(joystickGetDigital(MASTER, 8, JOY_UP))lower_lifter();
  else if(joystickGetDigital(MASTER, 8, JOY_DOWN))raise_lifter();
  else set_lifter_motors(0);
}
