#include "claw.h"

void update_claw() {
  static int last_error = 0;
  static enum claw_state state = CLAW_OPEN_STATE;
  if(joystickGetDigital(CLAW_CLOSE)){
    state = CLAW_CLOSE_STATE;
  }
  else if(joystickGetDigital(CLAW_OPEN)){
    state = CLAW_OPEN_STATE;
  } else {
    int p = 0;
    if(state == CLAW_OPEN_STATE) {
      p = getClawTicks() - CLAW_OPEN_VAL;
    } else {
      p = getClawTicks() - CLAW_CLOSE_VAL;
    }

<<<<<<< HEAD
=======
    //if(getClawTicks() < 1600) return;

>>>>>>> b1dcd7b066da52ff16cad1c5834b4ab23dad99fa
    int d = (p - last_error);
    int motor = CLAW_P * p;
    set_claw_motor(motor);
  }
}

void set_claw_motor(const int v){
  set_motor_immediate(CLAW_MOTOR, v);
}

unsigned int getClawTicks(){
  return analogRead(CLAW_POT);
}

void open_claw() {
  set_motor_immediate(CLAW_MOTOR, MAX_CLAW_SPEED);
}

void close_claw() {
  set_motor_immediate(CLAW_MOTOR, MIN_CLAW_SPEED);
}
