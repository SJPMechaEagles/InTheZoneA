#include "claw.h"

/**
* @brief Updates the claw motor values
* @author Chris Jerrett
**/
void update_claw() {
  //Set the Error used in calculating d
  static int last_error = 0;
  //Set the initial claw state to open
  static enum claw_state state = CLAW_OPEN_STATE;
  //Listen for input and either close or open the claw
  if(joystickGetDigital(CLAW_CLOSE)){
    state = CLAW_CLOSE_STATE;
  }
  else if(joystickGetDigital(CLAW_OPEN)){
    state = CLAW_OPEN_STATE;
  } else {
    //set the default motor speed
    int p = 0;
    //Change the base speed to the difference between the target
    // and the current value
    if(state == CLAW_OPEN_STATE) {
      p = getClawTicks() - CLAW_OPEN_VAL;
    } else {
      p = getClawTicks() - CLAW_CLOSE_VAL;
    }
    //Set the d value to the difference between the current p and the last p
    int d = (p - last_error);
    //Set last error for use the next time the function is run
    last_error = p;
    //Construct the final motor speed value
    int motor = CLAW_P * p + CLAW_D * d;
    //Set the motor speed
    set_claw_motor(motor);
  }
}

/**
* @brief sets the claw motor speed
* @author Chris Jerrett
**/
void set_claw_motor(const int v){
  set_motor_immediate(CLAW_MOTOR, v);
}

/**
* @brief Gets the claw position in potentiometer ticks
* @author Chris Jerrett
**/
unsigned int getClawTicks(){
  return analogRead(CLAW_POT);
}

/**
* @brief Drives the motors to open the claw
* @author Chris Jerrett
**/
void open_claw() {
  set_motor_immediate(CLAW_MOTOR, MAX_CLAW_SPEED);
}

/**
* @brief Drives the motors to close the claw
* @author Chris Jerrett
**/
void close_claw() {
  set_motor_immediate(CLAW_MOTOR, MIN_CLAW_SPEED);
}
