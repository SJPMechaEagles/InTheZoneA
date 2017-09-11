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
* @brief logging only info messages and higher.
* @author Chris Jerrett
* @date 9/10/17
**/
#define INFO 2

/**
* @brief logging only info debug.
* most verbose level
* @author Chris Jerrett
* @date 9/10/17
**/
#define DEBUG 3

unsigned int log_level = DEBUG;

/**
* @brief prints a error message and displays on lcd.
* Only will print and display if log_level is greater than NONE
* @see log_level
* @author Chris Jerrett
* @date 9/10/17
* @param error_message the message
**/
void error(const char *error_message) {
  if(log_level>NONE) {
    printf("[ERROR]: %s\n", error_message);
    lcd_clear();
    lcd_set_backlight(true);
    lcd_print(TOP_ROW, error_message);
  }
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
