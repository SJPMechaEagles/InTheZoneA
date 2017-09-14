/**
* @file menu.h
* @brief Contains menu functionality and abstraction.
* @author Chris Jerrett
* @date 9/9/2017
**/
#ifndef _MENU_H_
#define  _MENU_H_

#include <stdarg.h>
#include <API.h>
#include "vlib.h"
#include "lcd.h"
#include <float.h>
#include <limits.h>
#include <string.h>

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
  int_type,
  /**
  * @brief Menu type allowing user to select a float
  * The float type menu has a max, min and a step value. Each step is calculated.
  * Will return the index of the selected value.
  * Example: User goes forwards twice then it will return 2.
  **/
  float_type,
  /**
  * @brief Menu type allowing user to select a string from a array of strings.
  * Will return the index of the selected value.
  * Example: User goes forwards twice then it will return 2.
  **/
  string_type
};

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
  * @brief contains the minumum int value of menu.
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
  * Step is how much the int menu will increase of decrease with each press. Defualts to one
  * @author Chris Jerrett
  * @date 9/8/17
  **/
  int step;

  /**
  * @brief contains the minumum float value of menu.
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
  * Step is how much the int menu will increase of decrease with each press. Defualts to 1.0f
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
  * Step is how much the int menu will increase of decrease with each press. Defualts to one
  * @author Chris Jerrett
  * @date 9/8/17
  **/
  char prompt[16];
} menu_t;

/**
* @brief Static function that handles creation of menu.
* <em> Menu must be freed or will cause memory leak <em>
* @author Chris Jerrett
* @date 9/8/17
**/
static menu_t* create_menu(enum menu_type type, const char *prompt) {
  menu_t* menu = (menu_t*) malloc(sizeof(menu_t));
  menu->type = type;
  strcpy(menu->prompt, prompt);
  menu->min = INT_MAX;
  menu->min = INT_MIN;
  menu->step = 1;
  menu->min_f = FLT_MIN;
  menu->max_f = FLT_MAX;
  menu->step_f = 1;

  return menu;
}

/**
* @brief Creates a menu context, but does not display.
* <em> Menu must be freed or will cause memory leak <em>
*
* @param type the type of menu
* @see menu_type
* @param nums the number of elements passed to function
* @param prompt the prompt to diplay to user
* @param options the options to display for user
* @author Chris Jerrett
* @date 9/8/17
**/
menu_t* init_menu_var(enum menu_type type, unsigned int nums, char *prompt, char* options,...){
  menu_t* menu = create_menu(type, prompt);
  va_list values;
  char **options_array = (char**)malloc(sizeof(char*) * nums);
  va_start(values, options);
  for(unsigned int i; i < nums; i++){
    options_array[i] = va_arg(values, char*);
  }
  va_end(values);
  menu->options = options_array;
  menu->length = nums;
  return menu;
}

/**
* @brief Creates a menu context, but does not display.
* <em> Menu must be freed or will cause memory leak <em>
*
* @param type the type of menu
* @see menu_type
* @param min the minimum value
* @param max the maximum vlaue
* @param step the step value
* @param prompt the prompt to diplay to user
* @author Chris Jerrett
* @date 9/8/17
**/
menu_t* init_menu_int(enum menu_type type, int min, int max, int step, char* prompt){
  menu_t* menu = create_menu(type, prompt);
  menu->min = min;
  menu->max = max;
  menu->step = step;
  return menu;
}

/**
* @brief Creates a menu context, but does not display.
* <em> Menu must be freed or will cause memory leak! <em>
*
* @param type the type of menu
* @see menu_type
* @param min the minimum value
* @param max the maximum vlaue
* @param step the step value
* @param prompt the prompt to diplay to user
* @author Chris Jerrett
* @date 9/8/17
**/
menu_t* init_menu_float(enum menu_type type, float min, float max, float step, char* prompt){
  menu_t* menu = create_menu(type, prompt);
  menu->min_f = min;
  menu->max_f = max;
  menu->step_f = step;
  return menu;
}

/**
* @brief Static function that calculates the string from menu
*
* @param rtn the string to be written to
* @param menu the menu for prompt to be calculated from
* @author Chris Jerrett
* @date 9/8/17
**/
static void calculate_current_display(char* rtn, menu_t *menu) {
  if(menu->type == string_type){
    //Ignore warning
    rtn = (menu->options[menu->current % (menu->length)]);
  }
  if(menu->type == int_type) {
    int step = (menu->step);
    int min = (menu->min);
    int max = (menu->max);
    int value = menu->current * step;
    value = value < min ? min : value;
    value = value > max ? max : value;
    itoa(value, rtn, 4);
  }
  if(menu->type == float_type) {
    float step = (menu->step_f);
    float min = (menu->min_f);
    float max = (menu->max_f);
    float value = menu->current * step;
    value = value < min ? min : value;
    value = value > max ? max : value;

    ftoa(value, rtn, 5);
  }
}

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
int display_menu(menu_t *menu){
  lcd_print(TOP_ROW, menu->prompt);
  //Will exit if teleop or autonomous begin. This is extremely important if robot disconnects or resets.
  while(lcd_get_pressed_buttons().middle == RELEASED && !isEnabled()) {
    char val[16];
    calculate_current_display(val, menu);

    if(lcd_get_pressed_buttons().right == PRESSED) {
      menu->current += 1;
    }
    if(lcd_get_pressed_buttons().left == PRESSED) {
      menu->current -= 1;
    }
    delay(500);
  }
  return menu->current;
}

/**
* @brief Destroys a menu
* <em> Menu must be freed or will cause memory leak <em>
*
* @param menu the menu to free
* @see menu
* @author Chris Jerrett
* @date 9/8/17
**/
void denint_menu(menu_t *menu){
  free(menu->prompt);
  if(menu->options != NULL) free(menu->options);
  free(menu);
}

#endif
