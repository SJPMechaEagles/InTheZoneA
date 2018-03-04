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
#include <API.h>
Gyro gyro;

extern bool counter_clockwise;

static bool testIfReset() {
  FILE *f = fopen("de_cbble", "r");
  if (f == NULL) {
    f = fopen("de_cbble", "w");
    fputc('d', f);
    fflush(f);
    fclose(f);
    return false;
  }
  return true;
}

static void zero_ime() {
  imeReset(MID_LEFT_DRIVE);
  imeReset(MID_RIGHT_DRIVE);
}

static void setup_auton() {
  raise_main_lifter();
  delay(400);
  set_main_lifter_motors(0);
}

static void drive_towards_goal() {
  zero_ime();
  unsigned const int start_time = millis();
  int right_set_speed = 70;
  int left_set_speed = 70;

  int right_vel = 0;
  int left_vel = 0;

  for (;;) {
    lower_intake();
    if ((millis() - start_time) / 1000.0 > 1.7) {
      set_intake_motor(0);
    }
    set_side_speed(RIGHT, right_set_speed);
    set_side_speed(LEFT, left_set_speed);

    imeGetVelocity(MID_RIGHT_DRIVE, &right_vel);
    imeGetVelocity(MID_LEFT_DRIVE, &left_vel);

    const int diff = abs(right_vel) - abs(left_vel);

    int right_dist, left_dist = 0;
    imeGet(MID_LEFT_DRIVE, &right_dist);
    imeGet(MID_RIGHT_DRIVE, &left_dist);

    int ave_dist = (abs(right_dist) + abs(left_dist)) / 2;
    if (millis() - start_time > 2000) {
      set_side_speed(BOTH, 0);
      break;
    }

    delay(20);
  }
  zero_ime();
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
    set_side_speed(RIGHT, -70 * neg);
    set_side_speed(LEFT, 70 * neg);
    delay(10);
  } while (abs(diff) < abs(degrees));
  set_side_speed(BOTH, 0);
}

static void drive_distance(const int dist, const unsigned int speed,
                           float time) {
  zero_ime();
  int r_start;
  int l_start;
  imeGet(MID_RIGHT_DRIVE, &r_start);
  imeGet(MID_LEFT_DRIVE, &l_start);
  set_side_speed(BOTH, 0);
  int right_dist = 0;
  int left_dist = 0;
  imeGet(MID_RIGHT_DRIVE, &right_dist);
  const int ime_right_start = right_dist;

  imeGet(MID_LEFT_DRIVE, &left_dist);
  const int ime_left_start = left_dist;

  int right_set_speed = speed;
  int left_set_speed = speed;

  int right_vel = 0;
  int left_vel = 0;

  int ave_dist = 0;
  unsigned const int start_time = millis();
  do {
    if (abs(millis() - start_time) / 1000.0 > time)
      break;

    set_side_speed(RIGHT, right_set_speed);
    set_side_speed(LEFT, left_set_speed);

    imeGet(MID_RIGHT_DRIVE, &right_dist);
    imeGet(MID_LEFT_DRIVE, &left_dist);

    // ave_dist = max(abs(right_dist), abs(left_dist));

    const int diff =
        abs(right_vel - ime_right_start) - abs(left_vel - ime_left_start);

    delay(10);
  } while (abs(ave_dist) < dist);
  set_side_speed(BOTH, 0);
}

void drop_mobile_goal() {
  lower_intake();
  delay(1000);
  set_intake_motor(0);
}

void ten_point() {
  drive_distance(2000, -60, 2);
  int multiplier = counter_clockwise ? -1 : 1;
  multiplier = 1;
  set_claw_motor(0);
  turn(-215 * multiplier);
  drive_distance(200, 100, .3);
  drop_mobile_goal();
  delay(500);
  //  drive_distance(500, 50, 2);
  //  drop_mobile_goal();
  //  set_side_speed(BOTH, MIN_SPEED);
  //  delay(2000);
  set_side_speed(BOTH, 0);
}

void twenty_point() {
  drive_distance(2000, -60, 2);
  int multiplier = counter_clockwise ? -1 : 1;
  set_claw_motor(0);
  turn(-120 * multiplier);
  drive_distance(600, 80, .6);
  turn(-100 * multiplier);

  //  drive_distance(500, 50, 2);
  //  drop_mobile_goal();
  //  set_side_speed(BOTH, MIN_SPEED);
  //  delay(2000);
  set_side_speed(BOTH, 0);
  drive_distance(1600, 100, 2);
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
  if (testIfReset()) {
    error("File Reset");
    // return;
  }
  lower_secondary_lifter();
  delay(400);
  raise_secondary_lifter();
  delay(400);
  set_secondary_lifter_motors(0);

  info("Autonomous");
  init_slew();
  zero_ime();
  setup_auton();
  drive_towards_goal();
  delay(500);
  pick_up_mobile_goal();
  delay(300);
  claw_release_cone();
  delay(300);
  ten_point();
  drop_mobile_goal();
  set_side_speed(BOTH, -100);
  pick_up_mobile_goal();
  set_side_speed(BOTH, 0);
  delay(1000);
  gyroShutdown(gyro);
}
