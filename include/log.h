/**
* @file log.h
* @author Chris Jerrett
* @date 9/16/2017
* @brief Contains logging functions.
**/
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

/**
* @brief Initializes the error lcd system
* Only required if using lcd
* @author Chris Jerrett
* @date 9/10/17
* @param use_lcd whether to use the lcd
* @param lcd the lcd
**/
void init_error(bool use_lcd, FILE *lcd);

/**
* @brief prints a error message and displays on lcd.
* Only will print and display if log_level is greater than NONE
* @see log_level
* @author Chris Jerrett
* @date 9/10/17
* @param error_message the message
**/
void error(const char *error_message);

/**
* @brief prints a warning message and displays on lcd.
* Only will print and display if log_level is greater than NONE
* @see log_level
* @author Chris Jerrett
* @date 9/10/17
* @param warning_message the message
**/
void warning(const char *warning_message);

/**
* @brief prints a info message
*
* Only will print and display if log_level is greater than ERROR
* @see log_level
* @param info_message the message
**/
void info(const char *info_message);

/**
* @brief prints a info message
*
* Only will print and display if log_level is greater than info
* @see log_level
* @param debug_message the message
**/
void debug(const char *debug_message);


#endif
