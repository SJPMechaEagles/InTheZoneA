#include "goal.h"

void update_goal(){
  if(joystickGetDigital(MASTER, 7, JOY_UP)){
    raise_goal();
  }
  else if(joystickGetDigital(MASTER, 7, JOY_DOWN)){
    lower_goal();
  }
  else{
    motorSet(GOAL_MOTOR, 0);
  }
}

void raise_goal(){
  motorSet(GOAL_MOTOR, 120);
}

void lower_goal(){
  motorSet(GOAL_MOTOR, -120);
}
