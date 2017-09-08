#ifndef _MENU_H_
#define  _MENU_H_

#include "stdarg.h"
#include "stdlib.h"

enum menu_type {
  int_type,
  float_type,
  string_type
};

struct menu{
  enum menu_type type;
  char **options;
  int *length;
  int *min;
  int *max;
  int *step;
  float *min_f;
  float *max_f;
  float *step_f;
  int current;
};

static struct menu* create_menu(enum menu_type type) {
  struct menu* menu = (struct menu*) calloc(1, sizeof(struct menu));
  menu->type = type;
  return menu;
}

struct menu* init_menu(enum menu_type type, int nums, char* options,...){
  struct menu* menu = create_menu(type);
  va_list values;
  char **options_array = (char**)malloc(sizeof(char*) * nums);
  va_start(values, options);
  for(int i; i < nums; i++){
    options_array[i] = va_arg(values, char*);
  }
  va_end(values);
  menu->options = options_array;
  menu->length = &nums;
  return menu;
}

struct menu* init_menu(enum menu_type type, char **options, int length){
  struct menu* menu = create_menu(type);
  menu->options = options;
  menu->length = &length;
  return menu;
}

struct menu* init_menu(enum menu_type type, int min, int max, int step){
  struct menu* menu = create_menu(type);
  menu->min = &min;
  menu->max = &max;
  menu->step = &step;
  return menu;
}

struct menu* init_menu(enum menu_type type, float min, float max, float step){
  struct menu* menu = create_menu(type);
  menu->min_f = &min;
  menu->max_f = &max;
  menu->step_f = &step;
  return menu;
}

void denint_menu(struct menu *menu){
  free(menu);
}

#endif
