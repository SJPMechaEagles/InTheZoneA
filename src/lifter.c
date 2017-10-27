#include "lifter.h"

void set_lifter_motors(const char v) {
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
  if(joystickGetDigital(MASTER, 8, JOY_UP)) lower_lifter();
  else if(joystickGetDigital(MASTER, 8, JOY_DOWN)) raise_lifter();
  else set_lifter_motors(0);
  return;
}

float lifterPotentiometerToDegree(int x){
  //Magic math by Christian
  float f = (x - 680) / 4095.0 * 250.0;
  return f;
}

double getLifterHeight() {
  int degree = lifterPotentiometerToDegree(analogReadCalibrated(2));
  double sinDeg = sind(degree);
  float overshoot = (1.75 / sinDeg);
  return (LENGTH_LONG + LENGTH_SHORT + 2 * overshoot) * sinDeg + HEIGHT;
    //(LENGTH_LONG + overshoot) * sinDeg + HEIGHT + (LENGTH_SHORT + overshoot) * sinDeg;
}
