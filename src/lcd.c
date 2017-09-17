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
 static void lcd_assert() {
  if(lcd_port != NULL) {
    printf("LCD NULL!");
    exit(1);
  }
}

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

void lcd_clear() {
  lcd_assert();
  lcdClear(lcd_port);
}

void init_main_lcd(FILE *lcd) {
  lcdInit(lcd);
  lcd_port = lcd;
}

 void lcd_print(unsigned int line, const char *str) {
  lcd_assert();
  lcdSetText(lcd_port, line, str);
}

 void lcd_printf(unsigned int line, const char *format_str, ...) {
  lcd_assert();
  lcdPrint(lcd_port, line, format_str);
}

 void lcd_set_backlight(bool state) {
  lcd_assert();
  lcdSetBacklight(lcd_port, state);
}

void promt_confirmation(const char *confirm_text) {
  lcd_assert();
  lcd_print(1, confirm_text);
  while(lcd_get_pressed_buttons().middle != PRESSED){
    delay(200);
  }
}
