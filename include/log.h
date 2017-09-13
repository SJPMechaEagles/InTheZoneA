#ifndef _LOG_H_
#define _LOG_H_

#include <API.h>
#include "lcd.h"

/**
* @brief No logging.
* Should be used in competition to reduce serial communication
* @author Chris Jerrett
* @date 9/10/17
**/
#define NONE 0

/**
* @brief logging only errors.
* Also displays error to lcd
* @author Chris Jerrett
* @date 9/10/17
**/
#define ERROR 1

/**
* @brief logs errors and warnings.
* Also displays error to lcd
* @author Chris Jerrett
* @date 9/10/17
**/
#define WARNING 2

/**
* @brief logging only info messages and higher.
* @author Chris Jerrett
* @date 9/10/17
**/
#define INFO 3

/**
* @brief logging only info debug.
* most verbose level
* @author Chris Jerrett
* @date 9/10/17
**/
#define DEBUG 4

unsigned int log_level = DEBUG;
static FILE *log_lcd = NULL;

void init_error(bool use_lcd, FILE *lcd) {
  if(use_lcd) {
    lcdInit(lcd);
    lcd_port = lcd;
  }
}

static void log_info(const char *s, const char *mess) {
  printf("[%s]: %s\n", s, mess);
  lcdSetBacklight(log_lcd, true);
  lcdClear(log_lcd);
  lcdPrint(log_lcd, TOP_ROW, s);
  lcdPrint(log_lcd, BOTTOM_ROW, mess);
}

/**
* @brief prints a error message and displays on lcd.
* Only will print and display if log_level is greater than NONE
* @see log_level
* @author Chris Jerrett
* @date 9/10/17
* @param error_message the message
**/
void error(const char *error_message) {
  if(log_level>NONE)
    log_info("ERROR", error_message);
}

/**
* @brief prints a warning message and displays on lcd.
* Only will print and display if log_level is greater than NONE
* @see log_level
* @author Chris Jerrett
* @date 9/10/17
* @param warning_message the message
**/
void warning(const char *warning_message) {
  if(log_level>WARNING)
    log_info("WARNING", warning_message);
}

/**
* @brief prints a info message
*
* Only will print and display if log_level is greater than ERROR
* @see log_level
* @param info_message the message
**/
void info(const char *info_message) {
  if(log_level>ERROR) {
    printf("[INFO]: %s\n", info_message);
  }
}

/**
* @brief prints a info message
*
* Only will print and display if log_level is greater than info
* @see log_level
* @param debug_message the message
**/
void debug(const char *debug_message) {
  if(log_level>ERROR) {
    printf("[INFO]: %s\n", debug_message);
  }
}


#endif
