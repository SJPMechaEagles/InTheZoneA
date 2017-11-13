#include "claw.h"

void update_claw() {
  static int ticksOld = 0;
  if(joystickGetDigital(CLAW_CLOSE)){
    close_claw();
    ticksOld = getClawTicks();
  }
  else if(joystickGetDigital(CLAW_OPEN)){
    open_claw();
    ticksOld = getClawTicks();
  }
  else if(getClawTicks() < 200){
    set_claw_motor(20);
  }
  else if(getClawTicks() > 20){
    set_claw_motor(-20);
  }
  else{
    set_claw_motor(0);
  }
}

void set_claw_motor(const int v){
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
