#include "mobile_goal_intake.h"

void set_intake_motor(int n) { set_motor_immediate(MOBILE_INTAKE_MOTOR, n); }

extern void lower_intake();
void inline lower_intake() { set_intake_motor(-100); }

extern void raise_intake();
void inline raise_intake() { set_intake_motor(100); }

/**
 * @brief updates the mobile goal intake in teleop.
 */
void update_intake() {
  if (joystickGetDigital(MASTER, 8, JOY_UP)) {
    raise_intake();
  } else if (joystickGetDigital(MASTER, 8, JOY_DOWN)) {
    lower_intake();
  } else
    set_intake_motor(0);
}
