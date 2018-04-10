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
#include "auto.h"
#include "battery.h"
#include "encoders.h"
#include "gyro.h"
#include "lcd.h"
#include "lifter.h"
#include "log.h"
#include "main.h"
#include "menu.h"
#include "sensors.h"
#include "slew.h"
#include "toggle.h"
/*
 * Initilaizes the watchdog and feed task if watchdog is enabled
 */
void watchdogStart();

extern Ultrasonic lifter_ultrasonic;

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

enum FIELD_SIDE start_side = SIDE_NOT_SET;
enum FIELD_COLOR start_color = COLOR_NOT_SET;
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
  printf("START\n");
  buttonInit();
  init_encoders();
  init_error(true, uart2);
  init_main_lcd(uart1);
  info("Boot");
  info("Gyro Calibrate");
  init_main_gyro();
  setTeamName("9228A");
  lifter_ultrasonic = ultrasonicInit(4, 5);
  delay(5000);
  init_menu();
  menu_t *color_menu = init_menu_var(STRING_TYPE, (int *)&start_color, "COLOR?",
                                     2, "RED", "BLUE");
  menu_t *side_menu = init_menu_var(STRING_TYPE, (int *)&start_side, "SIDE?", 2,
                                    "Driver Side", "Not Driver Side");
  add_menu(color_menu);
  add_menu(side_menu);
  start_menu();
  setTeamName("9228A");
  info("Ready to run");
}
