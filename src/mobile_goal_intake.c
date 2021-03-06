#include "mobile_goal_intake.h"

static bool hold = false;
void set_intake_motor(int n) { set_motor_immediate(MOBILE_INTAKE_MOTOR, n); }

void lower_intake() { set_intake_motor(120); }

void raise_intake() { set_intake_motor(-120); }

void mobile_goal_down_pot() {
  lower_intake();
  printf("m1");
  while (analogRead(MOBILE_GOAL_POT_PORT) < MOBILE_GOAL_DOWN) {
    printf("%d\n", analogRead(MOBILE_GOAL_POT_PORT));
    delay(50);
  }
  printf("m2");
  set_intake_motor(0);
  printf("m3");
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

  } else if (joystickGetDigital(MASTER, 8, JOY_DOWN)) {
    lower_intake();
  } else {
    set_intake_motor(0);
  }
}
