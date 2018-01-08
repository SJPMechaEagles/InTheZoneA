#include "lcd.h"

/** The port of the initialized lcd **/
static FILE *lcd_port = NULL;

/**
 * @brief Asserts the lcd is initialized
 * Works by checking is the File *lcd_port is the default NULL
 * value and thus not set.
 * @author Chris Jerrett
 * @date 9/9/2017
 **/
static bool lcd_assert() {
  if (lcd_port == NULL) {
    printf("LCD NULL!");
    return false;
  }
  return true;
}

/**
 * @brief Returns the pressed buttons
 * @return a struct containing the states of all three buttons.
 * @author Chris Jerrett
 * @date 9/9/2017
 * @see lcd_buttons
 **/
lcd_buttons lcd_get_pressed_buttons() {
  lcd_assert();
  unsigned int btn_binary = lcdReadButtons(lcd_port);
  bool left = btn_binary & 0x1;   // 0001
  bool middle = btn_binary & 0x2; // 0010
  bool right = btn_binary & 0x4;  // 0100
  lcd_buttons btns;
  btns.left = left ? PRESSED : RELEASED;
  btns.middle = middle ? PRESSED : RELEASED;
  btns.right = right ? PRESSED : RELEASED;

  return btns;
}

/**
 * @brief Clears the lcd
 * @author Chris Jerrett
 * @date 9/9/2017
 **/
void lcd_clear() {
  lcd_assert();
  lcdClear(lcd_port);
}

/**
 * @brief Initializes the lcd screen.
 * Also will initialize the lcd_port var. Must be called before any lcd function
 *can be called.
 * @param lcd the urart port of the lcd screen
 * @see uart1
 * @see uart2
 * @author Chris Jerrett
 * @date 9/9/2017
 **/
void init_main_lcd(FILE *lcd) {
  lcd_port = lcd;
  lcdInit(lcd);
  lcd_clear();
}

/**
 * @brief prints a string to a line on the lcd
 * @param line the line to print on
 * @param str string to print
 * @author Chris Jerrett
 * @date 9/9/2017
 **/
void lcd_print(unsigned int line, const char *str) {
  lcd_assert();
  lcdSetText(lcd_port, line, str);
}

/**
 * @brief prints a formated string to a line on the lcd. Smilar to printf
 * @param line the line to print on
 * @param format_str format string string to print
 * @author Chris Jerrett
 * @date 9/9/2017
 **/
void lcd_printf(unsigned int line, const char *format_str, ...) {
  lcd_assert();
  lcdPrint(lcd_port, line, format_str);
}

/**
 * @brief sets the backlight of the lcd
 * @param state a boolean representing the state of the backlight. true = on,
 *false = off.
 * @author Chris Jerrett
 * @date 9/9/2017
 **/
void lcd_set_backlight(bool state) {
  lcd_assert();
  lcdSetBacklight(lcd_port, state);
}

/**
 * @brief Prompts the user to confirm a string.
 * User must press middle button to confirm.
 * Function is not thread safe and will stall a thread.
 *
 * @param confirm_text the text for the user to confirm.
 * @author Chris Jerrett
 * @date 9/9/2017
 **/
void promt_confirmation(const char *confirm_text) {
  lcd_assert();
  lcd_print(1, confirm_text);
  while (lcd_get_pressed_buttons().middle != PRESSED) {
    delay(200);
  }
}
