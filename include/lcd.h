/**
* @file lcd.h
* @author Chris Jerrett
* @date 9/9/2017
* @brief LCD wrapper functions and macros
**/

#ifndef _LCD_H_
#define  _LCD_H_

#include <API.h>
#include <string.h>
#include <stdarg.h>

/**
* @brief The top row on the lcd screen
* @author Chris Jerrett
* @date 9/9/2017
**/
#define TOP_ROW 1

/**
* @brief The bottom row on the lcd screen
* @author Chris Jerrett
* @date 9/9/2017
**/
#define BOTTOM_ROW 2

/**
* @brief Repressents the state of a button
*
* A button can be pressed of RELEASED. Release is false which is also 0.
* PRESSED is true or 1.
*
* @author Chris Jerrett
* @date 9/9/2017
**/
typedef enum {
  /** A released button **/
  RELEASED = false,
  /** A pressed button **/
  PRESSED = true,
} button_state;

/**
* @brief repreents the state of the lcd buttons
* @author Chris Jerrett
* @date 9/9/2017
**/
typedef struct {
  button_state left;
  button_state middle;
  button_state right;
} lcd_buttons;

/** The port of the initialized lcd **/
static FILE *lcd_port = NULL;

void lcd_set_backlight(bool state);

/**
* @brief Asserts the lcd is initialized
* Works by chekcing is the File *lcd_port is the default NULL
* value and thus not set.
* @author Chris Jerrett
* @date 9/9/2017
**/
 static void lcd_assert() {
  if(lcd_port != NULL) {
    printf("LCD NULL!");
    exit(1);
  }
}

/**
* @brief Returns the pressed buttons
* @return a struct containing the states of all three buttons.
* @author Chris Jerrett
* @date 9/9/2017
* @see lcd_buttons
**/
lcd_buttons lcd_get_pressed_buttons(){
  lcd_assert();
  unsigned int btn_binary = lcdReadButtons(lcd_port);
  bool left = btn_binary & 0x1;
  bool middle = btn_binary & 0x2;
  bool right = btn_binary & 0x4;
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
* Also will initialize the lcd_port var. Must be called before any lcd function can be called.
* @param lcd the urart port of the lcd scrren
* @see uart1
* @see uart2
* @author Chris Jerrett
* @date 9/9/2017
**/
void init_lcd(FILE *lcd) {
  lcdInit(lcd);
  lcd_port = lcd;
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
* @param state a boolean representing the state of the backlight. true = on, false = off.
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
  while(lcd_get_pressed_buttons().middle != PRESSED){
    delay(200);
  }
}

#endif
