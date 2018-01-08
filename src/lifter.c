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
  if (joystickGetDigital(LIFTER_DOWN) &&
      analogRead(MAIN_LIFTER_POT) < MAIN_LIFTER_MIN_HEIGHT) {
    set_secondary_lifter_motors(MAX_SPEED);
    set_main_lifter_motors(MIN_SPEED);
  } else if (joystickGetDigital(LIFTER_DOWN) &&
             analogRead(MAIN_LIFTER_POT) >= MAIN_LIFTER_MIN_HEIGHT) {
    set_secondary_lifter_motors(MAX_SPEED);
    set_main_lifter_motors(0);
  } else if (joystickGetDigital(LIFTER_UP) &&
             analogRead(SECONDARY_LIFTER_POT_PORT) <
                 SECONDARY_LIFTER_MAX_HEIGHT) {
    set_secondary_lifter_motors(MIN_SPEED);
    set_main_lifter_motors(0);
  } else if (joystickGetDigital(LIFTER_UP) &&
             analogRead(SECONDARY_LIFTER_POT_PORT) >=
                 SECONDARY_LIFTER_MAX_HEIGHT) {
    set_main_lifter_motors(MAX_SPEED);
    set_secondary_lifter_motors(MIN_SPEED);
  } else {
    set_secondary_lifter_motors(0);
    set_main_lifter_motors(0);
  }
  if (joystickGetDigital(LIFTER_DOWN) &&
      analogRead(SECONDARY_LIFTER_POT_PORT) < SECONDARY_LIFTER_MIN_HEIGHT) {
    set_secondary_lifter_motors(0);
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
