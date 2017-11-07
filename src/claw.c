#include "claw.h"

/*void update_claw(){
  static bool closed = false;
  if(closed){
    if((analogRead(CLAW_POT) - CLAW_CLOSE) > 20){
      close_claw();
    }
    else set_claw_motor(0);
  }
  else if(!closed){
    if((analogRead(CLAW_POT) - CLAW_OPEN) > 20){
      open_claw();
    }
    else set_claw_motor(0);
  }
}*/

void update_claw() {
  static bool changed = true;
  static int target = 0;
  if(joystickGetDigital(CLAW_OPEN)){
    changed = true;
    target = CLAW_OPEN;
    close_claw();
  } else if(joystickGetDigital(CLAW_CLOSE)) {
    changed = true;
    target = CLAW_CLOSE;
    open_claw();
  } else {
    static long long i = 0;
    if(changed) {
      target = getClawTicks();
      i = 0;
    }
    int p = target - getClawTicks();
    i += p;
    int d = target - getClawTicks();
    int motorVal = -p * CLAW_P + d * CLAW_D  + i * CLAW_I;
    //printf("%d\n", motorVal);

    set_claw_motor(motorVal);
    changed = false;
  }
}

void set_claw(enum claw_state state) {
  if(state == open) {
    set_claw_motor(100);
  }
}

void set_claw_motor(const char v){
  set_motor_immediate(CLAW_MOTOR, v);
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
