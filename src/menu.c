#include "menu.h"

static menu_t* create_menu(enum menu_type type, const char *prompt);
static void calculate_current_display(char* rtn, menu_t *menu);

/**
* @brief Static function that handles creation of menu.
* <em> Menu must be freed or will cause memory leak <em>
* @author Chris Jerrett
* @date 9/8/17
**/
static menu_t* create_menu(enum menu_type type, const char *prompt) {
  menu_t* menu = (menu_t*) malloc(sizeof(menu_t));
  if (!menu) {
    error("Menu Malloc");
  }
  menu->type = type;
  // Add one for null terminator
  size_t strlength = strlen(prompt) + 1;
  menu->prompt = (char*) malloc(strlength * sizeof(char));
  memcpy(menu->prompt, prompt, strlength);
  menu->max = INT_MAX;
  menu->min = INT_MIN;
  menu->step = 1;
  menu->min_f = FLT_MIN;
  menu->max_f = FLT_MAX;
  menu->step_f = 1;
  menu->current = 0;

  return menu;
}

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
menu_t* init_menu_var(enum menu_type type, const char *prompt, int nums,...){
  menu_t* menu = create_menu(type, prompt);
  va_list ap;
  char **options_array = (char**)calloc(sizeof(char*), nums);
  va_start(ap, nums);
  for(int i = 0; i < nums; i++){
    options_array[i] = (char*) va_arg(ap, char*);
    printf("%s\n", options_array[i]);
  }
  va_end(ap);
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
* @param max the maximum value
* @param step the step value
* @param prompt the prompt to display to user
* @author Chris Jerrett
* @date 9/8/17
**/
menu_t* init_menu_int(enum menu_type type, int min, int max, int step, const char* prompt){
  menu_t* menu = create_menu(type, prompt);
  menu->min = min;
  menu->max = max;
  menu->step = step;
  menu->current = 0;
  return menu;
}

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
menu_t* init_menu_float(enum menu_type type, float min, float max, float step, const char* prompt){
  menu_t* menu = create_menu(type, prompt);
  menu->min_f = min;
  menu->max_f = max;
  menu->step_f = step;
  return menu;
}

static void calculate_current_display(char* rtn, menu_t *menu) {
  if(menu->type == STRING_TYPE){
  int index = menu->current % menu->length;
  sprintf(rtn, "%s", menu->options[index]);
  printf("%s\n", rtn);
  return;
  }
  if(menu->type == INT_TYPE) {
    int step = (menu->step);
    int min = (menu->min);
    int max = (menu->max);
    int value = menu->current * step;
    if(value < min) {
      value = min;
      menu->current++;
    }
    if(value > max) {
      value = max;
      menu->current--;
    }
    sprintf(rtn, "%d", value);
  }
  if(menu->type == FLOAT_TYPE) {
    float step = (menu->step_f);
    float min = (menu->min_f);
    float max = (menu->max_f);
    float value = menu->current * step;
    value = value < min ? min : value;
    value = value > max ? max : value;


    ftoaa(value, rtn, 5);
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
  printf("printed prompt\n");
  //Will exit if teleop or autonomous begin. This is extremely important if robot disconnects or resets.
  char val[16];
  while(lcd_get_pressed_buttons().middle == RELEASED) {
    calculate_current_display(val, menu);

    if(lcd_get_pressed_buttons().right == PRESSED) {
      menu->current += 1;
    }
    if(lcd_get_pressed_buttons().left == PRESSED) {
      menu->current -= 1;
    }
    printf("%s\n", val);
    printf("%d\n",menu->current);
    lcd_print(2, val);
    delay(300);
  }
  printf("%d\n", menu->current);
  printf("return\n");
  lcd_clear();
  lcd_print(1, "Thk Cm Agn");
  lcd_print(2, val);
  delay(800);
  lcd_clear();
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
