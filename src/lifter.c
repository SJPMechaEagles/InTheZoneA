#include "lifter.h"
#include "log.h"

/**
 * @brief Sets the secondary lifter motors to the given value
 *
 * @param v value for the lifter motor. Between -128 - 127, any values outside
 *are clamped.
 * @author Chris Jerrett
 * @date 1/6/2018
 **/
void set_secondary_lifter_motors(const int v) {
  set_motor_immediate(MOTOR_SECONDARY_LIFTER, v);
}

/**
 * @brief Sets the main lifter motors to the given value
 *
 * @param v value for the lifter motor. Between -128 - 127, any values outside
 *are clamped.
 * @author Chris Jerrett
 * @date 9/9/2017
 **/
void set_main_lifter_motors(const int v) { set_motor_immediate(MOTOR_LIFT, v); }

/**
 * @brief Sets the lifter positions to the given value
 *
 * @param pos The height in inches
 * @author Chris Jerrett
 * @date 9/12/2017
 **/
void set_lifter_pos(int pos) {}

/**
 * @brief Raises the main lifter
 *
 * @author Christian DeSimone
 * @date 9/12/2017
 **/
void raise_main_lifter() { set_main_lifter_motors(MAX_SPEED); }

/**
 * @brief Lowers the main lifter
 *
 * @author Christian DeSimone
 * @date 9/12/2017
 **/
void lower_main_lifter() { set_main_lifter_motors(MIN_SPEED); }

/**
 * @brief Raises the main lifter
 *
 * @author Christian DeSimone
 * @date 9/12/2017
 **/
void raise_secondary_lifter() { set_secondary_lifter_motors(MAX_SPEED); }

/**
 * @brief Lowers the secondary lifter
 *
 * @author Christian DeSimone
 * @date 9/12/2017
 **/
void lower_secondary_lifter() { set_secondary_lifter_motors(MIN_SPEED); }

/**
 * @brief Updates the lifter in teleop.
 *
 * @author Chris Jerrett
 * @date 9/9/2017
 **/
void update_lifter() {
  static bool pid_on = false;
  static int second_target = 0;
  int second_motor_speed = 0;
  if(pid_on) {
    int curr = analogRead(SECONDARY_LIFTER_POT_PORT);
    static long long second_i = 0;
    static int second_last_p = 0;
    int second_p = curr - second_target;
    second_i += second_p;
    int second_d = second_last_p - second_p;
    second_motor_speed = SECONDARY_LIFTER_P * second_p + SECONDARY_LIFTER_I * second_i + SECONDARY_LIFTER_D * second_d;
    second_last_p = second_p;
  }

  if(joystickGetDigital(LIFTER_UP)){
    set_main_lifter_motors(MAX_SPEED);
  } else if(joystickGetDigital(LIFTER_DOWN)){
    set_main_lifter_motors(MIN_SPEED);
  }
  else{
    set_main_lifter_motors(0);
  }
  if(joystickGetDigital(SECONDARY_LIFTER_UP)){
    second_motor_speed = MIN_SPEED;
    second_target = analogRead(SECONDARY_LIFTER_POT_PORT);
  }
  else if(joystickGetDigital(SECONDARY_LIFTER_DOWN)){
    second_motor_speed = MAX_SPEED;
    second_target = analogRead(SECONDARY_LIFTER_POT_PORT);
  }
  set_secondary_lifter_motors(second_motor_speed);
  printf("motor speed: %d\n", second_motor_speed);
  pid_on = true;
}
/**
 * @brief height of the lifter in degrees from 0 height
 *
 * @param x the pot value
 * @return the positions in degrees
 * @author Chris Jerrett
 * @date 10/13/2017
 **/
float lifterPotentiometerToDegree(int x) {
  return (x - INIT_ROTATION) / TICK_MAX * DEG_MAX;
}

/**
 * @brief Gets the value of the lifter pot.
 *
 * @return the value of the pot.
 * @author Chris Jerrett
 * @date 9/9/2017
 **/
int getLifterTicks() { return analogRead(LIFTER); }

/**
 * @brief Gets the height of the lifter in inches.
 *
 * @return the height of the lifter.
 * @author Chris Jerrett
 * @date 9/17/2017
 **/
double getLifterHeight() {
  unsigned int ticks = getLifterTicks();
  return (-2 * pow(10, (-9 * ticks)) + 6 * (pow(10, (-6 * ticks * ticks))) +
          0.0198 * ticks + 2.3033);
}
