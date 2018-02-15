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
#include "gyro.h"
#include "lifter.h"
#include "log.h"
#include "mobile_goal_intake.h"
#include "slew.h"
Gyro gyro;

static void zero_ime() {
  imeReset(MID_LEFT_DRIVE);
  imeReset(MID_RIGHT_DRIVE);
}

static void setup_auton() {
  raise_main_lifter();
  delay(500);
  set_main_lifter_motors(0);
}

static void drive_towards_goal() {
  unsigned const int start_time = millis();
  int right_set_speed = 80;
  int left_set_speed = 80;

  int right_vel = 0;
  int left_vel = 0;

  for (;;) {
    lower_intake();
    if ((millis() - start_time) / 1000.0 > 1) {
      set_intake_motor(0);
    }
    set_side_speed(RIGHT, right_set_speed);
    set_side_speed(LEFT, left_set_speed);

    imeGetVelocity(MID_RIGHT_DRIVE, &right_vel);
    imeGetVelocity(MID_LEFT_DRIVE, &left_vel);

    const int diff = abs(right_vel) - abs(left_vel);

    right_set_speed -= .001 * diff;
    left_set_speed += .001 * diff;

    printf("RIGHT VEL: %d\n", right_vel);
    printf("LEFT VEL: %d\n", left_vel);
    printf("DIFF VEL: %d\n", diff);

    int right_dist, left_dist = 0;
    imeGet(MID_LEFT_DRIVE, &right_dist);
    imeGet(MID_RIGHT_DRIVE, &left_dist);

    int ave_dist = (abs(right_dist) + abs(left_dist)) / 2;
    if (ave_dist > 1600 || millis() - start_time > 2300) {
      info("exit");
      set_side_speed(BOTH, 0);
      break;
    }

    printf("RIGHT: %d\n", right_dist);
    printf("LEFT: %d\n", left_dist);
    printf("AVG: %d\n", ave_dist);

    delay(20);
  }
}

static void pick_up_mobile_goal() {
  raise_intake();
  delay(1000);
  set_intake_motor(0);
}

static void turn(const int degrees) {
  int start = gyroGet(gyro);
  int diff;
  int neg = abs(degrees) / degrees;
  do {
    diff = gyroGet(gyro) - start;
    set_side_speed(RIGHT, -100 * neg);
    set_side_speed(LEFT, 100 * neg);
    info("Turn");
    delay(10);
  } while (abs(diff) < abs(degrees));
  set_side_speed(BOTH, 0);
}

static void drive_distance(const int dist, const unsigned int speed) {
  info("Drive Distance");
  int right_dist = 0;
  int left_dist = 0;
  imeGet(MID_RIGHT_DRIVE, &right_dist);
  const int ime_right_start = right_dist;

  imeGet(MID_LEFT_DRIVE, &left_dist);
  const int ime_left_start = left_dist;

  int right_set_speed = 100;
  int left_set_speed = 100;

  int right_vel = 0;
  int left_vel = 0;

  do {
    set_side_speed(RIGHT, 100);
    set_side_speed(LEFT, 100);
    int ave_dist = (abs(right_dist) + abs(left_dist)) / 2;

    imeGetVelocity(MID_RIGHT_DRIVE, &right_vel);
    imeGetVelocity(MID_LEFT_DRIVE, &left_vel);

    const int diff = abs(right_vel) - abs(left_vel);

    right_set_speed -= .001 * diff;
    left_set_speed += .001 * diff;

    delay(10);
  } while (abs(dist) < dist);
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
  claw_release_cone();
  delay(500);
  set_claw_motor(0);
  info("5");
  turn(-180);
  drive_distance(4000, 100);
  gyroShutdown(gyro);
}
