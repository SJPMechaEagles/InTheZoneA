#include "lifter.h"

void set_lifter_motors(const int v) {
  set_motor_immediate(MOTOR_LIFT_TOP_RIGHT, v);
  set_motor_immediate(MOTOR_LIFT_TOP_LEFT, -v);
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
  static unsigned int target = 0;
  static int last_error = 0;
  static long long i = 0;
  if(joystickGetDigital(LIFTER_UP) || joystickGetDigital(LIFTER_UP_PARTNER)){
    changed = true;
    i = 0;
    target = getLifterTicks() + 200;
    lower_lifter();
  }
  else if(joystickGetDigital(LIFTER_DOWN) || joystickGetDigital(LIFTER_DOWN_PARTNER)) {
    changed = true;
    i = 0;
    target = getLifterTicks() - 300;
    raise_lifter();
  }
  else {
    int p = getLifterTicks() - target;
    int d = p - last_error;
    i += p;
    int motor = LIFTER_P * p + LIFTER_D * d + LIFTER_I * i;
    //printf("P: %f\t, D: %f\t, I: %f\n", p*LIFTER_P , d*LIFTER_D, i*LIFTER_I);
    set_lifter_motors(motor);
  }
}

float lifterPotentiometerToDegree(int x){
  return (x - TICK_DIFF) / TICK_MAX * DEG_MAX;
}

int getLifterTicks() {
  return analogReadCalibrated(LIFTER);
}


double getLifterHeight() {
  unsigned int ticks = getLifterTicks();
  return (-2 * pow(10, (-9 * ticks)) + 6 * (pow(10, (-6 * ticks * ticks))) + 0.0198 * ticks + 2.3033);
}
