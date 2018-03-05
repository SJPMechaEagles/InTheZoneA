#include "menu.h"

static TaskHandle menuTask;

/**
 * @brief Static function that handles creation of menu.
 * <em> Menu must be freed or will cause memory leak <em>
 * @author Chris Jerrett
 * @date 9/8/17
 **/
static menu_t *create_menu(enum menu_type type, int *returnValue,
                           const char *prompt);

/**
 * @brief Static function that calculates the string from menu
 *
 * @param rtn the string to be written to
 * @param menu the menu for the display to be calculated from
 * @author Chris Jerrett
 * @date 9/8/17
 **/
static void calculate_current_display(char *rtn, menu_t *menu);

/**
 * @brief Static function that handles creation of menu.
 * <em> Menu must be freed or will cause memory leak <em>
 * @author Chris Jerrett
 * @date 9/8/17
 **/
static menu_t *create_menu(enum menu_type type, int *returnValue,
                           const char *prompt) {
  menu_t *menu = (menu_t *)malloc(sizeof(menu_t));
  if (!menu) {
    error("Menu Malloc");
  }
  menu->type = type;
  // Add one for null terminator
  size_t strlength = strlen(prompt) + 1;
  menu->prompt = (char *)malloc(strlength * sizeof(char));
  memcpy(menu->prompt, prompt, strlength);
  menu->max = INT_MAX;
  menu->min = INT_MIN;
  menu->step = 1;
  menu->min_f = FLT_MIN;
  menu->max_f = FLT_MAX;
  menu->step_f = 1;
  menu->current = 0;
  menu->returnValue = returnValue;

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
menu_t *init_menu_var(enum menu_type type, int *returnValue, const char *prompt,
                      int nums, ...) {
  menu_t *menu = create_menu(type, returnValue, prompt);
  va_list ap;
  char **options_array = (char **)calloc(sizeof(char *), nums);
  va_start(ap, nums);
  for (int i = 0; i < nums; i++) {
    options_array[i] = (char *)va_arg(ap, char *);
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
menu_t *init_menu_int(enum menu_type type, int *returnValue, int min, int max,
                      int step, const char *prompt) {
  menu_t *menu = create_menu(type, returnValue, prompt);
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
menu_t *init_menu_float(enum menu_type type, int *returnValue, float min,
                        float max, float step, const char *prompt) {
  menu_t *menu = create_menu(type, returnValue, prompt);
  menu->min_f = min;
  menu->max_f = max;
  menu->step_f = step;
  return menu;
}

static void calculate_current_display(char *rtn, menu_t *menu) {
  if (menu->type == STRING_TYPE) {
    int index = menu->current % menu->length;
    sprintf(rtn, "%s", menu->options[index]);
    printf("%s\n", rtn);
    return;
  }
  if (menu->type == INT_TYPE) {
    int step = (menu->step);
    int min = (menu->min);
    int max = (menu->max);
    int value = menu->current * step + (menu->min + menu->max) / 2;
    if (value < min) {
      value = min;
      menu->current++;
    }
    if (value > max) {
      value = max;
      menu->current--;
    }
    sprintf(rtn, "%d", value);
  }
  if (menu->type == FLOAT_TYPE) {
    float step = (menu->step_f);
    float min = (menu->min_f);
    float max = (menu->max_f);
    float value = menu->current * step + (menu->min_f + menu->max_f) / 2;
    value = value < min ? min : value;
    value = value > max ? max : value;

    ftoaa(value, rtn, 5);
  }
}

static list_t *menus_list;

void add_menu(menu_t *menu) {
  list_node_t *node = list_node_new(menu);
  list_rpush(menus_list, node);
}

static void update_menu(void *param) {
  int index = 0;
  int length = list_length(menus_list);
  for (int i = 0; i < length; i++) {
    display_menu((menu_t *)list_rpop(menus_list)->val);
    char str[16];
    sprintf(str, "Displaying num: %s", str);
    debug(str);
  }
}

void init_menu() { menus_list = list_new(); }

void start_menu() {
  menuTask = taskCreate(update_menu, TASK_DEFAULT_STACK_SIZE, NULL,
                        TASK_DEFAULT_STACK_SIZE);
}

/**
 * @brief Displays a menu contex.
 * <em> Menu must be freed or will cause memory leak! <em> Will exit if robot is
 * enabled. This prevents menu from locking up system in even of a reset.
 *
 * @param menu the menu to display
 * @see menu_type
 * @author Chris Jerrett
 * @date 9/8/17
 **/
void display_menu(menu_t *menu) {
  lcd_print(TOP_ROW, menu->prompt);
  printf("printed prompt\n");
  // Will exit if teleop or autonomous begin. This is extremely important if
  // robot disconnects or resets.
  char val[16];
  while (lcd_get_pressed_buttons().middle == RELEASED) {
    calculate_current_display(val, menu);

    if (lcd_get_pressed_buttons().right == PRESSED) {
      menu->current += 1;
    }
    if (lcd_get_pressed_buttons().left == PRESSED) {
      menu->current -= 1;
    }
    printf("%s\n", val);
    printf("%d\n", menu->current);
    lcd_print(2, val);
    delay(300);
  }
  printf("%d\n", menu->current);
  printf("return\n");
  lcd_clear();
  lcd_print(1, "Selected:");
  lcd_print(2, val);
  delay(600);
  lcd_clear();
  if (menu->type == STRING_TYPE) {
    *(menu->returnValue) = menu->current;
  } else if (menu->type == INT_TYPE) {
    int curr = menu->current;
    *(menu->returnValue) =
        menu->current * menu->step + (menu->min + menu->max) / 2;
  } else if (menu->type == FLOAT_TYPE) {
    int curr = menu->current;
    *(menu->returnValue) =
        menu->current * menu->step_f + (menu->min_f + menu->max_f) / 2.0;
  }
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
void denint_menu(menu_t *menu) {
  free(menu->prompt);
  if (menu->options != NULL)
    free(menu->options);
  free(menu);
}
