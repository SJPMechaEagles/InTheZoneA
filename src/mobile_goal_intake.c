#include "mobile_goal_intake.h"
#include "partner.h"

static void set_intake_motor(int n) {
  set_motor_immediate(INTAKE_MOTOR, n);
}

static void lower_intake() {
  set_intake_motor(100);
}

static void raise_intake() {
  set_intake_motor(-100);
}

void updateIntake() {
  if(joystickGetDigital(MASTER, 7, JOY_UP) && (get_mode() == MAIN_CONTROLLER_MODE)
  || joystickGetDigital(PARTNER, 6, JOY_UP) && get_mode() == PARTNER_CONTROLLER_MODE) {
    raise_intake();
  }
  else if(joystickGetDigital(MASTER, 7, JOY_DOWN) && (get_mode() == MAIN_CONTROLLER_MODE)
  || joystickGetDigital(PARTNER, 6, JOY_DOWN) && get_mode() == PARTNER_CONTROLLER_MODE){
    lower_intake();
  }
  else set_intake_motor(0);
}
