#ifndef _MENU_H_
#define  _MENU_H_

#include "stdarg.h"
#include "stdlib.h"
#include <API.h>

#define PRESSED true
#define RELESED false

static bool lcd_initialized = false;
static FILE *lcd_port;

enum menu_type {
  int_type,
  float_type,
  string_type
};

typedef struct buttons {
  bool left;
  bool middle;
  bool right;
} buttons_t;

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
};

buttons_t get_pressed_buttons(){
  unsigned int btn_binary = lcdReadButtons(lcd_port);
  bool left = btn_binary & 0x1;
  bool middle = btn_binary & 0x2;
  bool right = btn_binary & 0x4;
  buttons_t btns;
  btns.left = left;
  btns.middle = middle;
  btns.right = right;

  return btns;
}

struct menu_result {
  int result_index;
  void* value;
};

static struct menu* create_menu(enum menu_type type) {
  struct menu* menu = (struct menu*) calloc(1, sizeof(struct menu));
  menu->type = type;
  return menu;
}

struct menu* init_menu(enum menu_type type, unsigned int nums, char* options,...){
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

struct menu* init_menu(enum menu_type type, char **options, unsigned int length){
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

struct menu_result display_menu(struct menu *menu){
  while(get_pressed_buttons().middle == RELESED) {
      if(get_pressed_buttons().right == PRESSED) {
        menu->current += 1;
      }
      if(get_pressed_buttons().left == PRESSED) {
        menu->current -= 1;
      }
      delay(500);
  }
  struct menu_result results;
  results.result_index = menu->current;
  return results;
}

void init_lcd(FILE *lcd_port) {
  lcdInit (lcd_port);
  lcd_initialized = true;
}

void denint_menu(struct menu *menu){
  free(menu);
}

#endif
