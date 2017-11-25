/** @file auto.c
 * @brief File for autonomous code
 *
 * This file should contain the user autonomous() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"
#include "auto.h"

/*
 * Runs the user autonomous code. This function will be started in its own task with the default
 * priority and stack size whenever the robot is enabled via the Field Management System or the
 * VEX Competition Switch in the autonomous mode. If the robot is disabled or communications is
 * lost,  the autonomous task will be stopped by the kernel. Re-enabling the robot will restart
 * the task, not re-start it from where it left off.
 *
 * Code running in the autonomous task cannot access information from the VEX Joystick. However,
 * the autonomous function can be invoked from another task if a VEX Competition Switch is not
 * available, and it can access joystick information if called in this way.
 *
 * The autonomous task may exit, unlike operatorControl() which should never exit. If it does
 * so, the robot will await a switch to another mode or disable/enable cycle.
 */
void autonomous() {
  init_slew();


  delay(10);
  printf("auto\n");
  int counts_drive_left;
  int counts_drive_right;
  int counts_drive;
  imeReset(MID_LEFT_DRIVE);
  imeReset(MID_RIGHT_DRIVE);
  imeGet(MID_LEFT_DRIVE, &counts_drive_left);
  imeGet(MID_RIGHT_DRIVE, &counts_drive_right);
  counts_drive = counts_drive_left + counts_drive_right;
  counts_drive /= 2;
  close_claw();

  delay(300);
  //unsigned long time = millis();
  while(analogRead(LIFTER) < GOAL_HEIGHT){
    set_lifter_motors(-127);
  }
  set_lifter_motors(0);
<<<<<<< HEAD
  while(counts_drive_left < 530){
=======
  while(counts_drive_left < STOP_ONE){
>>>>>>> b1dcd7b066da52ff16cad1c5834b4ab23dad99fa
    set_side_speed(BOTH, 127);
    imeGet(MID_LEFT_DRIVE, &counts_drive_left);
    imeGet(MID_RIGHT_DRIVE, &counts_drive_right);
    counts_drive = counts_drive_left + counts_drive_right;
    counts_drive /= 2;
    //if(millis() - time > 1000) break;
  }
  set_side_speed(BOTH, 0);
  delay(1000);
  open_claw();
  delay(1000);
  deinitslew();
}
