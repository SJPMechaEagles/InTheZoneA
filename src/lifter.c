#include "lifter.h"

void set_lifter_motors(const int v) {
  set_motor_immediate(MOTOR_LIFT_TOP_RIGHT, -v);
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
  static bool first_run = true;
  if(first_run) {
    target = getLifterTicks();
    first_run = false;
  }
  static int last_error = 0;
  static long long i = 0;
  if((joystickGetDigital(LIFTER_UP) && get_mode() == MAIN_CONTROLLER_MODE)
   || (joystickGetDigital(LIFTER_UP_PARTNER) && get_mode() == PARTNER_CONTROLLER_MODE)){
    changed = true;
    i = 0;
    target = getLifterTicks() + 200;
    lower_lifter();
  }
  else if((joystickGetDigital(LIFTER_DOWN) && get_mode() == MAIN_CONTROLLER_MODE)
   || (joystickGetDigital(LIFTER_DOWN_PARTNER) && get_mode() == PARTNER_CONTROLLER_MODE)) {
    changed = true;
    i = 0;
    target = getLifterTicks();
    raise_lifter();
  }
  else if(joystickGetDigital(LIFTER_DRIVER_LOAD) && get_mode() == MAIN_CONTROLLER_MODE){
    changed = true;
    i = 0;
    int k = 0;
    if(getLifterTicks() < 1270){
      lower_lifter();

    }
    if(getLifterTicks() > 1230){
      raise_lifter();
      //k = 100;
    }
    target = 1250;
    //raise_lifter();
  }
  else {
    if(get_mode() == PARTNER_CONTROLLER_MODE){
      set_lifter_motors(0);
      return;
    }
    int p = getLifterTicks() - target;
    int d = p - last_error;
    i += p;
    int motor = LIFTER_P * p + LIFTER_D * d + LIFTER_I * i;
    if (motor < 10) {
        set_lifter_motors(0);
    } else {
        set_lifter_motors(motor);
    }
    
  }
}

float lifterPotentiometerToDegree(int x){
  return (x - TICK_DIFF) / TICK_MAX * DEG_MAX;
}

int getLifterTicks() {
  return analogRead(LIFTER);
}


double getLifterHeight() {
  unsigned int ticks = getLifterTicks();
  return (-2 * pow(10, (-9 * ticks)) + 6 * (pow(10, (-6 * ticks * ticks))) + 0.0198 * ticks + 2.3033);
}
