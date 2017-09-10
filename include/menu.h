#ifndef _MENU_H_
#define  _MENU_H_

#include <stdarg.h>
#include <API.h>
#include "vlib.h"
#include "lcd.h"
#include <float.h>


enum menu_type {
  int_type,
  float_type,
  string_type
};

struct menu{
  enum menu_type type;
  char **options;
  unsigned int *length;
  int *min;
  int *max;
  int *step;
  float *min_f;
  float *max_f;
  float *step_f;
  int current;
  char* prompt;
};

struct menu_result {
  int result_index;
  void* value;
};

static struct menu* create_menu(enum menu_type type, char *prompt) {
  struct menu* menu = (struct menu*) calloc(1, sizeof(struct menu));
  menu->type = type;
  menu->prompt = prompt;
  return menu;
}

struct menu* init_menu(enum menu_type type, unsigned int nums, char *prompt, char* options,...){
  struct menu* menu = create_menu(type, prompt);
  va_list values;
  char **options_array = (char**)malloc(sizeof(char*) * nums);
  va_start(values, options);
  for(unsigned int i; i < nums; i++){
    options_array[i] = va_arg(values, char*);
  }
  va_end(values);
  menu->options = options_array;
  menu->length = &nums;
  return menu;
}

struct menu* init_menu(enum menu_type type, char **options, unsigned int length, char* prompt){
  struct menu* menu = create_menu(type, prompt);
  menu->options = options;
  menu->length = &length;
  return menu;
}

struct menu* init_menu(enum menu_type type, int min, int max, int step, char* prompt){
  struct menu* menu = create_menu(type, prompt);
  menu->min = &min;
  menu->max = &max;
  menu->step = &step;
  return menu;
}

struct menu* init_menu(enum menu_type type, float min, float max, float step, char* prompt){
  struct menu* menu = create_menu(type, prompt);
  menu->min_f = &min;
  menu->max_f = &max;
  menu->step_f = &step;
  return menu;
}

static void calculate_current_display(char* rtn, struct menu *menu) {
  if(menu->type == string_type){
    //Ignore warning
    rtn = (menu->options[menu->current % *(menu->length)]);
  }
  if(menu->type == int_type) {
    int step = (menu->step) == NULL ? 1 : *(menu->step);
    int min = (menu->min) == NULL ? 100 : *(menu->min);
    int max = (menu->max) == NULL ? -100 : *(menu->max);
    int value = menu->current * step;
    value = value < min ? min : value;
    value = value > max ? max : value;
    itoa(value, rtn, 4);
  }
  if(menu->type == float_type) {
    float step = (menu->step_f) == NULL ? 1 : *(menu->step_f);
    float min = (menu->min_f) == NULL ? 100 : *(menu->min_f);
    float max = (menu->max_f) == NULL ? -100 : *(menu->max_f);
    float value = menu->current * step;
    value = value < min ? min : value;
    value = value > max ? max : value;

    ftoa(value, rtn, 5);
  }
}

struct menu_result display_menu(struct menu *menu){
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
  struct menu_result results;
  results.result_index = menu->current;
  return results;
}

void denint_menu(struct menu *menu){
  free(menu);
}

#endif
