#include "lifter.h"

/**
* @brief Sets the lifter motors to the given value
*
* @param v value for the lifter motor. Between -128 - 127, any values outside are clamped.
* @author Chris Jerrett
* @date 9/9/2017
**/
void set_lifter_motors(const int v) {
  set_motor_immediate(MOTOR_LIFT_TOP_RIGHT, -v);
  set_motor_immediate(MOTOR_LIFT_TOP_LEFT, -v);
}

/**
* @brief Sets the lifter positions to the given value
*
* @param pos The height in inches
* @author Chris Jerrett
* @date 9/12/2017
**/
void set_lifter_pos(int pos) {

}

/**
* @brief Raises the lifter
*
* @author Christian DeSimone
* @date 9/12/2017
**/
void raise_lifter(){
  set_lifter_motors(MAX_SPEED);
}

/**
* @brief Lowers the lifter
*
* @author Christian DeSimone
* @date 9/12/2017
**/
void lower_lifter(){
  set_lifter_motors(MIN_SPEED);
}

/**
* @brief Updates the lifter in teleop.
*
* @author Chris Jerrett
* @date 9/9/2017
**/
void update_lifter() {
  //Establish variables to be used repeatedly
  static bool changed = true;
  static unsigned int target = 0;
  static bool first_run = true;
  //Set the target to the current height for the first run
  if(first_run) {
    target = getLifterTicks();
    first_run = false;
  }
  //Establish the error as 0
  static int last_error = 0;
  static long long i = 0;
  //Check the buttons on the controller indicated by the controller mode
  if((joystickGetDigital(LIFTER_UP) && get_mode() == MAIN_CONTROLLER_MODE)
   || (joystickGetDigital(LIFTER_UP_PARTNER) && get_mode() == PARTNER_CONTROLLER_MODE)){
    changed = true;
    i = 0;
    //Change the target and start the motion
    target = getLifterTicks() + 200;
    lower_lifter();
  }
  else if((joystickGetDigital(LIFTER_DOWN) && get_mode() == MAIN_CONTROLLER_MODE)
   || (joystickGetDigital(LIFTER_DOWN_PARTNER) && get_mode() == PARTNER_CONTROLLER_MODE)) {
    changed = true;
    i = 0;
    //Change the target and start the motion
    target = getLifterTicks();
    raise_lifter();
  }
  //Raise the lifter to the driver load height
  else if(joystickGetDigital(LIFTER_DRIVER_LOAD) && get_mode() == MAIN_CONTROLLER_MODE){
    changed = true;
    i = 0;
    int k = 0;
    if(getLifterTicks() < 1270){
      lower_lifter();

    }
    if(getLifterTicks() > 1230){
      raise_lifter();
    }
    target = 1250;
  }
  //Change lifter motor values based upon the target
  else {
    //Don't if we are using the partner controller
    if(get_mode() == PARTNER_CONTROLLER_MODE){
      set_lifter_motors(0);
      return;
    }
    //Define the proportion, derivative, and integral to be used in the motor speed
    int p = getLifterTicks() - target;
    int d = p - last_error;
    last_error = p;
    i += p;
    int motor = LIFTER_P * p + LIFTER_D * d + LIFTER_I * i;
    //Avoid wasting battery if value is insignificant
    if (motor < THRESHOLD) {
        set_lifter_motors(0);
    } else {
        set_lifter_motors(motor);
    }

  }
}

/**
* @brief height of the lifter in degrees from 0 height
*
* @param x the pot value
* @return the positions in degrees
* @author Chris Jerrett
* @date 10/13/2017
**/
float lifterPotentiometerToDegree(int x){
  return (x - INIT_ROTATION) / TICK_MAX * DEG_MAX;
}

/**
* @brief Gets the value of the lifter pot.
*
* @return the value of the pot.
* @author Chris Jerrett
* @date 9/9/2017
**/
int getLifterTicks() {
  return analogRead(LIFTER);
}

/**
* @brief Gets the height of the lifter in inches.
*
* @return the height of the lifter.
* @author Chris Jerrett
* @date 9/17/2017
**/
double getLifterHeight() {
  unsigned int ticks = getLifterTicks();
  return (-2 * pow(10, (-9 * ticks)) + 6 * (pow(10, (-6 * ticks * ticks))) + 0.0198 * ticks + 2.3033);
}
