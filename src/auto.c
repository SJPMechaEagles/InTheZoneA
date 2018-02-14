/** @file auto.c
 * @brief File for autonomous code
 *
 * This file should contain the user autonomous() function and any functions
 * related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */
#include "auto.h"
#include "lifter.h"
#include "log.h"
#include "slew.h"

static void zero_ime() {
  imeReset(MID_LEFT_DRIVE);
  imeReset(MID_RIGHT_DRIVE);
}

static void setup_auton() {
  raise_main_lifter();
  delay(300);
  set_main_lifter_motors(0);
}

static void drive_towards_goal() {
  unsigned const int start_time = millis();
  int right_set_speed = 100;
  int left_set_speed = 100;

  int right_vel = 0;
  int left_vel = 0;

  for (;;) {
    lower_intake();
    if ((millis() - start_time) / 1000.0 > 2) {
      set_intake_motor(0);
    }
    set_side_speed(RIGHT, right_set_speed);
    set_side_speed(LEFT, left_set_speed);

    imeGetVelocity(MID_RIGHT_DRIVE, &right_vel);
    imeGetVelocity(MID_LEFT_DRIVE, &left_vel);

    const int diff = abs(right_vel) - abs(left_vel);

    right_set_speed -= .0005 * diff;
    left_set_speed += .0005 * diff;

    printf("RIGHT VEL: %d\n", right_vel);
    printf("LEFT VEL: %d\n", left_vel);
    printf("DIFF VEL: %d\n", diff);

    int right_dist, left_dist = 0;
    imeGet(MID_LEFT_DRIVE, &right_dist);
    imeGet(MID_RIGHT_DRIVE, &left_dist);

    int ave_dist = (abs(right_dist) + abs(left_dist)) / 2;
    if (ave_dist > 2000) {
      set_side_speed(BOTH, 0);
      break;
    }

    printf("RIGHT: %d\n", right_dist);
    printf("LEFT: %d\n", left_dist);
    printf("DIFF: %d\n", ave_dist);

    delay(20);
  }
}

static void pick_up_mobile_goal() {
  raise_intake();
  delay(1000);
}

static void turn(int degrees) {
  do {

  } while (false);
}

/*
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. If the robot is disabled or communications is lost,  the autonomous
 * task will be stopped by the kernel. Re-enabling the robot will restart the
 * task, not re-start it from where it left off.
 *
 * Code running in the autonomous task cannot access information from the VEX
 * Joystick. However, the autonomous function can be invoked from another task
 * if a VEX Competition Switch is not available, and it can access joystick
 * information if called in this way.
 *
 * The autonomous task may exit, unlike operatorControl() which should never
 * exit. If it does so, the robot will await a switch to another mode or
 * disable/enable cycle.
 */
void autonomous() {
  info("0");
  init_slew();
  info("1");
  zero_ime();
  info("2");
  setup_auton();
  info("3");
  drive_towards_goal();
  info("4");
  pick_up_mobile_goal();
  info("5");
  turn(-180);
}
