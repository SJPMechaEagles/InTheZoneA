/**
* @file menu.h
* @brief Contains menu functionality and abstraction.
* @author Chris Jerrett
* @date 9/9/2017
**/
#ifndef _MENU_H_
#define _MENU_H_

#include "lcd.h"
#include "API.h"
#include <string.h>
#include <limits.h>
#include <float.h>
#include <vlib.h>
#include "log.h"

/**
* @brief Represents the different types of menus.
* @author Chris Jerrett
* @date 9/8/17
* @see menu.h
* @see menu_t
* @see create_menu
* @see init_menu
* @see display_menu
* @see menu_type
**/
enum menu_type {
  /**
  * @brief Menu type allowing user to select a integer.
  * The integer type menu has a max, min and a step value. Each step is calculated.
  * Will return the index of the selected value.
  * Example: User goes forwards twice then it will return 2.
  **/
  INT_TYPE,
  /**
  * @brief Menu type allowing user to select a float
  * The float type menu has a max, min and a step value. Each step is calculated.
  * Will return the index of the selected value.
  * Example: User goes forwards twice then it will return 2.
  **/
  FLOAT_TYPE,
  /**
  * @brief Menu type allowing user to select a string from a array of strings.
  * Will return the index of the selected value.
  * Example: User goes forwards twice then it will return 2.
  **/
  STRING_TYPE
};

/**
* @brief Represents a specific instance of a menu.
* Will cause a memory leak if not deinitialized via denint_menu.
* @author Chris Jerrett
* @date 9/8/17
* @see menu.h
* @see menu_t
* @see create_menu
* @see init_menu
* @see display_menu
* @see menu_type
* @see denint_menu
**/
typedef struct menu_t{
  /**
  * @brief contains the type of menu.
  * @author Chris Jerrett
  * @date 9/8/17
  **/
  enum menu_type type;

  /**
  * @brief contains the array of string options.
  * @author Chris Jerrett
  * @date 9/8/17
  **/
  char **options;

  /**
  * @brief contains the length of options char**.
  * @author Chris Jerrett
  * @date 9/8/17
  **/
  unsigned int length;

  /**
  * @brief contains the minimum int value of menu.
  * Defaults to minimum int value
  * @author Chris Jerrett
  * @date 9/8/17
  **/
  int min;

  /**
  * @brief contains the maximum int value of menu.
  * Defaults to minimum int value
  * @author Chris Jerrett
  * @date 9/8/17
  **/
  int max;

  /**
  * @brief contains the step int value of menu.
  * Step is how much the int menu will increase of decrease with each press. Defaults to one
  * @author Chris Jerrett
  * @date 9/8/17
  **/
  int step;

  /**
  * @brief contains the minimum float value of menu.
  * Defaults to minimum int value
  * @author Chris Jerrett
  * @date 9/8/17
  **/
  float min_f;

  /**
  * @brief contains the maximum float value of menu.
  * Defaults to minimum int value
  * @author Chris Jerrett
  * @date 9/8/17
  **/
  float max_f;

  /**
  * @brief contains the step float value of menu.
  * Step is how much the int menu will increase of decrease with each press. Defaults to 1.0f
  * @author Chris Jerrett
  * @date 9/8/17
  **/
  float step_f;
  /**
  * @brief contains the current index of menu.
  * @author Chris Jerrett
  * @date 9/8/17
  **/
  int current;
  /**
  * @brief contains the prompt to display on the first line.
  * Step is how much the int menu will increase of decrease with each press. Defaults to one
  * @author Chris Jerrett
  * @date 9/8/17
  **/
  char *prompt;
} menu_t;

/**
* @brief Static function that handles creation of menu.
* <em> Menu must be freed or will cause memory leak <em>
* @author Chris Jerrett
* @date 9/8/17
**/
static menu_t* create_menu(enum menu_type type, const char *prompt);

/**
* @brief Creates a menu context, but does not display.
* <em> Menu must be freed or will cause memory leak <em>
*
* @param type the type of menu
* @see menu_type
* @param nums the number of elements passed to function
* @param prompt the prompt to display to user
* @param options the options to display for user
* @author Chris Jerrett
* @date 9/8/17
**/
menu_t* init_menu_var(enum menu_type type, unsigned int nums, const char *prompt, char* options,...);

/**
* @brief Creates a menu context, but does not display.
* <em> Menu must be freed or will cause memory leak <em>
*
* @param type the type of menu
* @see menu_type
* @param min the minimum value
* @param max the maximum value
* @param step the step value
* @param prompt the prompt to display to user
* @author Chris Jerrett
* @date 9/8/17
**/
menu_t* init_menu_int(enum menu_type type, int min, int max, int step, const char* prompt);

/**
* @brief Creates a menu context, but does not display.
* <em> Menu must be freed or will cause memory leak! <em>
*
* @param type the type of menu
* @see menu_type
* @param min the minimum value
* @param max the maximum value
* @param step the step value
* @param prompt the prompt to display to user
* @author Chris Jerrett
* @date 9/8/17
**/
menu_t* init_menu_float(enum menu_type type, float min, float max, float step, const char* prompt);

/**
* @brief Static function that calculates the string from menu
*
* @param rtn the string to be written to
* @param menu the menu for prompt to be calculated from
* @author Chris Jerrett
* @date 9/8/17
**/
static void calculate_current_display(char* rtn, menu_t *menu);

/**
* @brief Displays a menu context, but does not display.
* <em> Menu must be freed or will cause memory leak! <em> Will exit if robot is enabled. This prevents menu
* from locking up system in even of a reset.
*
* @param menu the menu to display
* @see menu_type
* @author Chris Jerrett
* @date 9/8/17
**/
int display_menu(menu_t *menu);

/**
* @brief Destroys a menu
* <em> Menu must be freed or will cause memory leak <em>
*
* @param menu the menu to free
* @see menu
* @author Chris Jerrett
* @date 9/8/17
**/
void denint_menu(menu_t *menu);

#endif
