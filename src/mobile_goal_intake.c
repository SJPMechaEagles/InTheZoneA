#include "mobile_goal_intake.h"

static bool hold = false;
void set_intake_motor(int n) { set_motor_immediate(MOBILE_INTAKE_MOTOR, n); }

extern void lower_intake();
void inline lower_intake() { set_intake_motor(80); }

extern void raise_intake();
void inline raise_intake() { set_intake_motor(-80); }

void mobile_goal_down_pot() {
  lower_intake();
  while (analogRead(MOBILE_GOAL_POT_PORT) < MOBILE_GOAL_DOWN) {
    delay(15);
  }
  set_intake_motor(0);
}

void mobile_goal_up_pot() {
  raise_intake();
  for (; analogRead(MOBILE_GOAL_POT_PORT) > MOBILE_GOAL_UP; delay(15)) {
  }
  set_intake_motor(0);
}
/**
 * @brief updates the mobile goal intake in teleop.
 */
void update_intake() {
  if (joystickGetDigital(MASTER, 8, JOY_UP)) {
    raise_intake();
    hold = true;
  } else if (joystickGetDigital(MASTER, 8, JOY_DOWN)) {
    lower_intake();
    hold = false;
  } else {
    if (hold) {
      set_intake_motor(20);
    } else {
      set_intake_motor(0);
    }
  }
}
