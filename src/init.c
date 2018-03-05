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

bool counter_clockwise = true;

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
  info("Boot");
  setTeamName("9228A");

  init_error(true, uart2);
  debug("init error sys");

  if (!init_encoders())
    error("Encoders failed");

  info("Gyro Calibrate");
  gyro = gyroInit(3, 230);

  lifter_ultrasonic = ultrasonicInit(4, 5);

  init_main_lcd(uart1);

  init_menu();

  int rtn_val1 = -1;
  menu_t *direction_menu =
      init_menu_var(STRING_TYPE, &rtn_val1, "Turn Direction?", 2, "CCW", "CW");

  int rtn_val2 = -1;
  menu_t *point_menu =
      init_menu_var(STRING_TYPE, &rtn_val2, "Turn Direction?", 2, "CCW", "CW");

  int rtn_val3 = -1;
  menu_t *delay_menu = init_menu_int(INT_TYPE, &rtn_val3, 0, 2000, 100,
                                     "Autonomous Start Delay");

  add_menu(direction_menu);
  add_menu(point_menu);
  add_menu(delay_menu);

  start_menu();

  info("Ready to run");
}
