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
#include "log.h"
#include "slew.h"

int fiveorten = 1700;

/**
 * @brief sets up the IMEs for the autonomous portion.
 * @author Christian DeSimone, Chris Jerrett
 * @param counts_drive_left The encoder value from the left motors
 * @param counts_drive_right The encoder value from the right motors
 * @param counts_drive The average encoder value from both sides
 **/
static inline void setup_ime_auton(int *counts_drive_left,
                                   int *counts_drive_right, int *counts_drive) {
  imeReset(MID_LEFT_DRIVE);
  imeReset(MID_RIGHT_DRIVE);
  // Set initial values for how far the wheels have gone
  imeGet(MID_LEFT_DRIVE, counts_drive_left);
  imeGet(MID_RIGHT_DRIVE, counts_drive_right);
  *counts_drive = *counts_drive_left + *counts_drive_right;
  *counts_drive /= 2;
}
/**
 * @brief Starts the auntonomous program.
 * @author Chris Jerrett, Christian DeSimone
 **/
static inline void
start_auton() { // starts the slew rate controller to prevent ptc trips
  init_slew();

  delay(10);
  info("AUTO");
}

/**
 * @brief utility function which deploys the secondary lifter at the start of autonomous.
 * @author Christian DeSimone, Chris Jerrett
 **/
void deploy_seoncdary_lifter() {
  while (analogRead(SECONDARY_LIFTER_POT_PORT) < DEPLOY_HEIGHT) {
    set_secondary_lifter_motors(MIN_SPEED);
  }
  set_secondary_lifter_motors(0);
}

/**
 * @brief utility function which raises the second lifter to its maximum height
 * @author Chris Jerrett, Christian DeSimone
 * @see MAX_HEIGHT
 **/
void auton_raise_sec_lifter_max() {
  while (analogRead(SECONDARY_LIFTER_POT_PORT) < MAX_HEIGHT) {
    set_secondary_lifter_motors(MIN_SPEED);
  }
  set_secondary_lifter_motors(0);
}

/**
 * @brief utility function to raise the mainlifter to the mobile goal height
 * @author Chris Jerrett, Christian DeSimone
 **/
void auton_rasie_main_lifter() {
  while (analogRead(MAIN_LIFTER_POT) < MOBILE_GOAL_HEIGHT) {
    set_main_lifter_motors(MAX_SPEED);
  }
  set_main_lifter_motors(0);
}
/**
 * @brief Drives the robot forward until it reaches the mobile goal
 * @author Christian DeSimone, Chris Jerrett
 **/
void auton_drive_towards_mobile_goal(int counts_drive, int counts_drive_left,
                                     int counts_drive_right) {
  while (counts_drive < MOBILE_GOAL_DISTANCE) {
    set_side_speed(BOTH, 127);
    // Restablish the distance traveled
    imeGet(MID_LEFT_DRIVE, &counts_drive_left);
    imeGet(MID_RIGHT_DRIVE, &counts_drive_right);
    counts_drive = counts_drive_left + counts_drive_right;
    counts_drive /= 2;
  }
}
void auton_drive_towards_stationary_goal(int counts_drive, int counts_drive_left, int counts_drive_right){
  while (counts_drive < STATIONARY_GOAL_DISTANCE){
    set_side_speed(BOTH, 127);
    imeGet(MID_LEFT_DRIVE, &counts_drive_left);
    imeGet(MID_RIGHT_DRIVE, &counts_drive_right);
    counts_drive = counts_drive_left + counts_drive_right;
    counts_drive /= 2;
  }
}
/**
 * @brief Rotates the robot 180 degrees clockwise
 * @author Chris Jerrett, Christian DeSimone
 **/
void auton_turn_180() {
  int ang = 0;
  while (ang < HALF_ROTATE) {
    ang += calculate_encoder_angle();
    set_side_speed(LEFT, MAX_SPEED);
    set_side_speed(RIGHT, MIN_SPEED);
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
void autonomous() {
  start_auton();
  //return;

  // How far the left wheels have gone
  int counts_drive_left;
  // How far the right wheels have gone
  int counts_drive_right;
  // The average distance traveled forward
  int counts_drive;

  // Reset the integrated motor controllers
  setup_ime_auton(&counts_drive_left, &counts_drive_right, &counts_drive);
  info("break 0");
  // Deploy claw
  deploy_seoncdary_lifter();
  info("break 1");

  info("break 2");
  set_secondary_lifter_motors(0);

  // Grab pre-load cone
  //delay(300);

//  auton_raise_sec_lifter_max();
  // Raise the lifter
//  auton_rasie_main_lifter();
  // Drive towards the goal

  //lower_intake();
  delay(500);
  //set_intake_motor(0);
 set_side_speed(BOTH, 127);
 set_main_lifter_motors(MAX_SPEED);
 lower_intake();
 delay(600);
 set_main_lifter_motors(0);

 delay(500);
 set_intake_motor(0);
 delay(600);
  //auton_drive_towards_mobile_goal(counts_drive, counts_drive_left,
    //hedck you chris                              counts_drive_right);
  // Stop moving
  set_side_speed(BOTH, 0);
  raise_intake();
  delay(1000);
  set_intake_motor(0);
  deploy_seoncdary_lifter();
  set_main_lifter_motors(MIN_SPEED);
  delay(400);
  set_main_lifter_motors(0);
  set_claw_motor(MIN_CLAW_SPEED);
  delay(750);
  set_claw_motor(0);
  set_side_speed(RIGHT, 127);
  set_side_speed(LEFT, -127);
  delay(1100);
  set_side_speed(BOTH, 0);
  set_main_lifter_motors(MAX_SPEED);
  delay(300);
  set_side_speed(BOTH, 127);
  delay(fiveorten);
  set_side_speed(BOTH, 0);
  lower_intake();
  delay(500);
  set_intake_motor(0);
  set_side_speed(BOTH, -127);
  delay(500);
  raise_intake();
  delay(500);
  set_side_speed(BOTH, 0);

  //raise_intake();
  //delay(300);
  //set_intake_motor(0);

  // Drop the cone on the goal
  //claw_release_cone();


//  auton_turn_180();



  //lower_intake();
  //delay(500);
  //set_intake_motor(0);

  set_side_speed(BOTH, -127);
  delay(1000);
  set_side_speed(BOTH, 0);



  deinitslew();
}
void garbo_auton(){
  // How far the left wheels have gone
  int counts_drive_left;
  // How far the right wheels have gone
  int counts_drive_right;
  // The average distance traveled forward
  int counts_drive;

  // Reset the integrated motor controllers
  setup_ime_auton(&counts_drive_left, &counts_drive_right, &counts_drive);
  info("break 0");

  deploy_seoncdary_lifter();
  raise_main_lifter();
  delay(500);
  set_main_lifter_motors(0);
  auton_drive_towards_stationary_goal(counts_drive, counts_drive_left, counts_drive_right);
  set_side_speed(BOTH, 0);
  claw_release_cone();

}
