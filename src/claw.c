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
  else if(getClawTicks() - ticksOld < 100){
    set_claw_motor(10);
  }
  else if(getClawTicks() - ticksOld > -100){
    set_claw_motor(-10);
  }
  else{
    set_claw_motor(0);
  }
  /*//static bool changed = true;
  static long long i = 0;
  static int target = CLAW_CLOSE_VAL;
  if(joystickGetDigital(CLAW_OPEN)){
    //changed = true;
    target = CLAW_OPEN_VAL;
    i = 0;
  } else if(joystickGetDigital(CLAW_CLOSE)) {
    //changed = true;
    target = CLAW_CLOSE_VAL;
    i = 0;
  } else {
    int p = target - getClawTicks();
    i += p;
    int d = target - getClawTicks();
    int motorVal = p * CLAW_P + d * CLAW_D  + i * CLAW_I;
    printf("P: %f\t, D: %f\t, I: %f\n", p*CLAW_P , d*CLAW_D, i*CLAW_I);
    printf("MOTOR: %d\n", -motorVal);

    set_claw_motor(-motorVal);
    //changed = false;

  }
  */
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
