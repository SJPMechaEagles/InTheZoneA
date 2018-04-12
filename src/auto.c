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

static void setup_auton() {
  info("setup_auton");
  raise_main_lifter();
  delay(400);
  set_main_lifter_motors(0);
}

static void drive_towards_goal() {
  info("Drive Towards Goal");
  unsigned const int start_time = millis();
  int right_set_speed = 80;
  int left_set_speed = 80;

  int right_vel = 0;
  int left_vel = 0;

  for (;;) {
    lower_intake();
    if ((millis() - start_time) / 1000.0 > .8) {
      set_intake_motor(0);
    }
    set_side_speed(RIGHT, right_set_speed);
    set_side_speed(LEFT, left_set_speed);
    if ((millis() - start_time) / 1000.0 > 1.9){
      break;
    }
    delay(30);
  }
  set_side_speed(BOTH, 0);
}

static void pick_up_mobile_goal() {
  raise_intake();
  delay(1500);
  set_intake_motor(0);
}

static void drop_mobile_goal() {
  info("drop_mobile_goal");
  lower_intake();
  delay(1000);
  set_intake_motor(0);
}

static void turn(const int degrees) {
  int start = gyroGet(gyro);
  int diff;
  int neg = abs(degrees) / degrees;
  do {
    diff = gyroGet(gyro) - start;
    set_side_speed(RIGHT, -80 * neg);
    set_side_speed(LEFT, 80 * neg);
    info("Turn");
    delay(10);
  } while (abs(diff) < abs(degrees));
  set_side_speed(BOTH, 0);
}

void drive_back_to_scoring_zone() {
  info("drive_back_to_scoring_zone");
  unsigned const int start_time = millis();
  for (;;) {
    set_side_speed(BOTH, MIN_SPEED + 40);
    delay(10);
    if ((millis() - start_time) / 1000.0 < 1.6)
      break;
  }
  set_side_speed(BOTH, 0);
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

/*
 * New autonomous routine: load preload cone, go to mobile goal, pick up mobile
 * goal, stack the preload cone, go forward, pick up and stack another cone, go
 * forward, pick up and stack the thrid cone, pick up and stack the fourth cone,
 * turn around, finally drop mobile goal in the 20 or 10 point zone.
 */
void autonomous_many_cones() {

  // gyroTurn(-170, GYRO_TURN_SPEED_MIN_FAST);
}

void autonomous() {
  printf("yes");
  init_slew();
  printf("1");
  delay(50);
  printf("2");
  // Deploy (put down) mobile lifter and raise main lifter a bit
  lower_secondary_lifter();
  raise_main_lifter();
  delay(300);
  raise_secondary_lifter();
  delay(200);
  printf("3");
  set_main_lifter_motors(0);
  delay(100);
  set_secondary_lifter_motors(0);
  printf("4");
  mobile_goal_down_pot();
  delay(100);
  printf("5");
  // go forward until robot reaches the mobile goal
  set_side_speed(BOTH, 80);
  delay(1600);
  //driveDistance(800, 80, NULL, NULL);
  set_side_speed(BOTH, 0);
  delay(500);
  printf("6");
  //drop the preload cone
  pick_up_mobile_goal();
  //delay(500);
  lower_main_lifter();
  delay(500);
  set_main_lifter_motors(0);
  claw_release_cone();
  delay(500);
  raise_main_lifter();
  delay(300);
  set_main_lifter_motors(0);
  set_side_speed(BOTH, 120);
  delay(380);
  set_side_speed(BOTH, 0);
  lower_secondary_lifter();
  claw_grab_cone();
  delay(200);
  lower_main_lifter();
  delay(700);
  set_main_lifter_motors(0);
  printf("6a");
  do {
    raise_secondary_lifter();
  } while( analogRead(SECONDARY_LIFTER_POT_PORT) < 1300);
  set_secondary_lifter_motors(0);
  printf("6b");
  raise_main_lifter();
  delay(500);
  set_main_lifter_motors(0);
  raise_secondary_lifter();
  delay(300);
  set_secondary_lifter_motors(0);
  lower_main_lifter();
  delay(200);
  set_main_lifter_motors(0);
  claw_release_cone();

  //move_main_lifter_to();
  printf("7");

  // pick up mobile goal and drop preload cone

  // pick up and stack the second to fourth cones
  for (int i = 0; i < 3; i++) {

    printf("%d \n", i);
  }
//  autonomous_many_cones();
  return;

  drive_back_to_scoring_zone();

  set_side_speed(BOTH, MAX_SPEED);
  delay(2000);
  set_side_speed(BOTH, 0);

  delay(1000);
  turn(-40);
  set_side_speed(BOTH, MAX_SPEED / 2);
  delay(500);
  set_side_speed(BOTH, 0);

  drop_mobile_goal();
  set_side_speed(BOTH, MIN_SPEED);
  delay(1000);
  set_side_speed(BOTH, 0);
  gyroShutdown(gyro);
}
