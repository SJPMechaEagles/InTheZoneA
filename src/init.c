/** @file init.c
 * @brief File for initialization code
 *
 * This file should contain the user initialize() function and any functions
 * related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */
#include "battery.h"
#include "encoders.h"
#include "lcd.h"
#include "lifter.h"
#include "log.h"
#include "main.h"
#include "menu.h"
#include "sensors.h"
#include "slew.h"

extern Ultrasonic lifter_ultrasonic;
extern Gyro gyro;

/*
 * Runs pre-initialization code. This function will be started in kernel mode
 * one time while the VEX Cortex is starting up. As the scheduler is still
 * paused, most API functions will fail.
 *
 * The purpose of this function is solely to set the default pin modes
 * (pinMode()) and port states (digitalWrite()) of limit switches, push buttons,
 * and solenoids. It can also safely configure a UART port (usartOpen()) but
 * cannot set up an LCD (lcdInit()).
 *
 */
void initializeIO() { watchdogInit(); }

/* @brief Initialization code to be run at startup of the cortex
 * @author Chris Jerrett
 * Runs user initialization code. This function will be started in its own task
 * with the default priority and stack size once when the robot is starting up.
 * It is possible that the VEXnet communication link may not be fully
 * established at this time, so reading from the VEX Joystick may fail.
 *
 * This function should initialize most sensors (gyro, encoders, ultrasonics),
 * LCDs, global variables, and IMEs.
 *
 * This function must exit relatively promptly, or the operatorControl() and
 * autonomous() tasks will not start. An autonomous mode selection menu like the
 * pre_auton() in other environments can be implemented in this task if desired.
 */
void initialize() {
  if (isEnabled() && isOnline()) {
    error("Robot Reset");
    // Return to opt control
    return;
  }
  init_error(true, uart2);
  info("init error");
  init_main_lcd(uart1);
  // Chech batteries
  if (!battery_level_acceptable()) {
    menu_t *bat_menu = init_menu_var(STRING_TYPE, "Main or 9V Dead", 1, "Okay");
    // execution paused till user confirms
    display_menu(bat_menu);
  }
  menu_t *t =
      init_menu_var(STRING_TYPE, "Auton Zone", 2, "Five Pt.", "Ten Pt.");
  int opt = display_menu(t);
  info("Gyro Calibrate");
  gyro = gyroInit(3, 230);
  setTeamName("9228A");
  if (!init_encoders())
    error("Encoders failed");
  lifter_ultrasonic = ultrasonicInit(4, 5);
  info("Ready to run");
}
