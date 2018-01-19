
static enum claw_state state = CLAW_NEUTRAL_STATE;

extern bool lifter_autostack_running;

/**
 * @brief Updates the claw motor values
 * @author Chris Jerrett
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
 **/
void set_claw_motor(const int v) { set_motor_immediate(CLAW_MOTOR, v); }

/**
 * @brief Drives the motors to grab a cone
 * @author Chris Jerrett
 **/
void claw_grab_cone() { set_motor_immediate(CLAW_MOTOR, MAX_CLAW_SPEED); }

/**
 * @brief Drives the motors to release a cone
 * @author Chris Jerrett
 **/
void claw_release_cone() { set_motor_immediate(CLAW_MOTOR, MIN_CLAW_SPEED); }
