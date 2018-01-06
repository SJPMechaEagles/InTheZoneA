#include "mobile_goal_intake.h"
#include "partner.h"
#include "log.h"

static void set_intake_motor(int n) {
  set_motor_immediate(INTAKE_MOTOR, n);
}

static void lower_intake() {
  set_intake_motor(-100);
}

static void raise_intake() {
  set_intake_motor(100);
}

/**
* @brief updates the mobile goal intake in teleop.
*/
void update_intake() {
  if(joystickGetDigital(MASTER, 7, JOY_UP)) {
    raise_intake();
  }
  else if(joystickGetDigital(MASTER, 7, JOY_DOWN)){
    lower_intake();
  }
  else set_intake_motor(0);
}
