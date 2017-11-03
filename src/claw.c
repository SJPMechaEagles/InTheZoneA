#include "claw.h"

void update_claw() {
  static bool changed = true;
  static int target = 0;
  if(joystickGetDigital(CLAW_OPEN)){
    changed = true;
    target = getClawTicks();
    close_claw();
  }
  else if(joystickGetDigital(CLAW_CLOSE)) {
    changed = true;
    target = getClawTicks();
    open_claw();
  }
  else {
    static int i = 0;
    if(changed) {
      target = getClawTicks();
      i = 0;
    }
    int p = target - getClawTicks();
    i += p;
    int d = target - getClawTicks();
    int motorVal = -p/CLAW_P - d/CLAW_D -i/CLAW_I;
    //printf("%d\n", motorVal);

    set_claw_motor(motorVal);
    changed = false;
  }
}


void set_claw_motor(const char v){
  set_motor_slew(CLAW_MOTOR, v);
}

unsigned int getClawTicks(){
  return analogReadCalibrated(CLAW_POT);
}

void open_claw() {
  set_motor_immediate(CLAW_MOTOR, MAX_CLAW_SPEED);
}

void close_claw() {
  set_motor_immediate(CLAW_MOTOR, MIN_CLAW_SPEED);
}
