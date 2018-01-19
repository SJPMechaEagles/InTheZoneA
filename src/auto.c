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
#include "main.h"

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
	//starts the slew rate controller to prevent ptc trips
  init_slew();

  delay(10);
	info("AUTO");
  // How far the left wheels have gone
  int counts_drive_left;
  // How far the right wheels have gone
  int counts_drive_right;
  // The average distance traveled forward
  int counts_drive;

  // Reset the integrated motor controllers
  imeReset(MID_LEFT_DRIVE);
  imeReset(MID_RIGHT_DRIVE);
  // Set initial values for how far the wheels have gone
  imeGet(MID_LEFT_DRIVE, &counts_drive_left);
  imeGet(MID_RIGHT_DRIVE, &counts_drive_right);
  counts_drive = counts_drive_left + counts_drive_right;
  counts_drive /= 2;
	info("break 0");
  // Deploy claw
  while (analogRead(SECONDARY_LIFTER_POT_PORT) < DEPLOY_HEIGHT) {
    set_secondary_lifter_motors(MAX_SPEED);
  }
  set_secondary_lifter_motors(0);
	info("break 1");

  //while (analogRead(SECONDARY_LIFTER_POT_PORT) > LOWEST_HEIGHT) {
  //  set_secondary_lifter_motors(MIN_SPEED);
  //}
	info("break 2");
  set_secondary_lifter_motors(0);

  // Grab pre-load cone
  //close_claw();
  delay(300);
  //set_claw_motor(0);

  while (analogRead(SECONDARY_LIFTER_POT_PORT) < MAX_HEIGHT) {
    set_secondary_lifter_motors(MAX_SPEED);
  }
  set_secondary_lifter_motors(0);
  // Raise the lifter
  while (analogRead(MAIN_LIFTER_POT) < MOBILE_GOAL_HEIGHT) {
    set_main_lifter_motors(MAX_SPEED);
  }
  set_main_lifter_motors(0);
  // Drive towards the goal

  lower_intake();
  delay(300);
  set_intake_motor(0);

  while (counts_drive < MOBILE_GOAL_DISTANCE) {
    set_side_speed(BOTH, 127);
    // Restablish the distance traveled
    imeGet(MID_LEFT_DRIVE, &counts_drive_left);
    imeGet(MID_RIGHT_DRIVE, &counts_drive_right);
    counts_drive = counts_drive_left + counts_drive_right;
    counts_drive /= 2;
  }
  // Stop moving
  set_side_speed(BOTH, 0);
  delay(1000);

  raise_intake();
  delay(300);
  set_intake_motor(0);

  // Drop the cone on the goal
  open_claw();
  delay(1000);

  int ang = 0;
  while (ang < HALF_ROTATE) {
    ang += calculate_encoder_angle();
    set_side_speed(LEFT, MAX_SPEED);
    set_side_speed(RIGHT, MIN_SPEED);
  }
  set_side_speed(BOTH, 0);

  counts_drive = 0;

  while (counts_drive < MOBILE_GOAL_DISTANCE + ZONE_DISTANCE) {
    set_side_speed(BOTH, 127);
    // Restablish the distance traveled
    imeGet(MID_LEFT_DRIVE, &counts_drive_left);
    imeGet(MID_RIGHT_DRIVE, &counts_drive_right);
    counts_drive = counts_drive_left + counts_drive_right;
    counts_drive /= 2;
  }

  lower_intake();
  delay(300);
  set_intake_motor(0);

  set_side_speed(BOTH, MIN_SPEED);
  delay(1000);
  set_side_speed(BOTH, 0);

  deinitslew();
}
