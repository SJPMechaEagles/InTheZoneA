#include "lifter.h"

void set_lifter_motors(const char v) {
  set_motor_slew(MOTOR_LIFT_TOP_RIGHT, v);
  set_motor_slew(MOTOR_LIFT_TOP_LEFT, -v);
}

void set_lifter_pos(int pos) {

}

void raise_lifter(){
  set_lifter_motors(MAX_SPEED);
}

void lower_lifter(){
  set_lifter_motors(MIN_SPEED);
}

void update_lifter() {
  static bool changed = true;
  static int target = 0;
  if(joystickGetDigital(LIFTER_UP)){
    changed = true;
    target = getLifterTicks();
    lower_lifter();
  }
  else if(joystickGetDigital(LIFTER_DOWN)) {
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
    int motorVal = -p/LIFTER_P - d/LIFTER_D -i/LIFTER_I;
    printf("%d\n", motorVal);

    set_lifter_motors(motorVal);
    changed = false;
  }
}

float lifterPotentiometerToDegree(int x){
  return (x - TICK_DIFF) / TICK_MAX * DEG_MAX;
}

unsigned int getLifterTicks() {
  return analogReadCalibrated(LIFTER);
}


double getLifterHeight() {
  unsigned int ticks = getLifterTicks();
  return (-2 * pow(10, (-9 * ticks)) + 6 * (pow(10, (-6 * ticks * ticks))) + 0.0198 * ticks + 2.3033);
}
