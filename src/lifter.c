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
  static bool changed = true;
  static int target = 0;
  if(joystickGetDigital(MASTER, 8, JOY_UP)){
    changed = true;
    target = getLifterTicks();
    lower_lifter();
  }
  else if(joystickGetDigital(MASTER, 8, JOY_DOWN)) {
    changed = true;
    target = getLifterTicks();
    raise_lifter();
  }
  else {
    static int i = 0;
    if(changed) {
      target = getLifterTicks();
      i = 0;
    }
    int p = target - getLifterTicks();
    i += p;
    int d = target - getLifterTicks();
    int motorVal = -p/10 - d/100 -i/400;
    printf("%d\n", motorVal);

    set_lifter_motors(motorVal);
    changed = false;
  }
}

float lifterPotentiometerToDegree(int x){
  //Magic math by Christian
  float f = (x - 680) / 4095.0 * 250.0;
  return f;
}

int getLifterTicks() {
  return analogReadCalibrated(2);
}


double getLifterHeight() {
  int degree = lifterPotentiometerToDegree(analogReadCalibrated(2));
  double sinDeg = sind(degree);
  float overshoot = (1.75 / sinDeg);
  return (LENGTH_LONG + LENGTH_SHORT + 2 * overshoot) * sinDeg + HEIGHT;
    //(LENGTH_LONG + overshoot) * sinDeg + HEIGHT + (LENGTH_SHORT + overshoot) * sinDeg;
}
