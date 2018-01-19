#include "claw.h"
#include "lifter.h"
#include "log.h"
#include "toggle.h"
static enum claw_state state = CLAW_NEUTRAL_STATE;

extern bool lifter_autostack_running;

/**
 * @brief Updates the claw motor values
 * @author Chris Jerrett
 * @see CLAW_CLOSE
 * @see CLAW_CLOSE_STATE
 * @see CLAW_OPEN
 * @see CLAW_OPEN_STATE
 * @see CLAW_NEUTRAL_STATE
 * @see MAX_CLAW_SPEED
 * @see MIN_CLAW_SPEED
 **/
void update_claw() {
  if (lifter_autostack_running)
    return;
  if (joystickGetDigital(CLAW_CLOSE)) {
    state = CLAW_CLOSE_STATE;
  } else if (joystickGetDigital(CLAW_OPEN)) {
    state = CLAW_OPEN_STATE;
  } else {
    state = CLAW_NEUTRAL_STATE;
  }

  if (state == CLAW_CLOSE_STATE) {
    set_claw_motor(MAX_CLAW_SPEED);
  } else if (state == CLAW_OPEN_STATE) {
    set_claw_motor(MIN_CLAW_SPEED);
  } else {
    set_claw_motor(0);
  }
}

/**
 * @brief sets the claw motor speed
 * @author Chris Jerrett
 * @see CLAW_MOTOR
 **/
void set_claw_motor(const int v) { set_motor_immediate(CLAW_MOTOR, v); }

/**
 * @brief Drives the motors to open the claw
 * @author Chris Jerrett
 * @see CLAW_MOTOR
 * @see MAX_CLAW_SPEED
 **/
void open_claw() { set_motor_immediate(CLAW_MOTOR, MAX_CLAW_SPEED); }

/**
 * @brief Drives the motors to close the claw
 * @author Chris Jerrett
 * @see CLAW_MOTOR
 * @see MIN_CLAW_SPEED
 **/
void close_claw() { set_motor_immediate(CLAW_MOTOR, MIN_CLAW_SPEED); }
