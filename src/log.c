#include "log.h"

unsigned int log_level = INFO;
static FILE *log_lcd = NULL;

void init_error(bool use_lcd, FILE *lcd) {
  if(use_lcd) {
    lcdInit(lcd);
    log_lcd = lcd;
  }
}

static void log_info(const char *s, const char *mess) {
  printf("[%s]: %s\n", s, mess);
  lcdSetBacklight(log_lcd, true);
  lcdClear(log_lcd);
  lcdPrint(log_lcd, TOP_ROW, s);
  lcdPrint(log_lcd, BOTTOM_ROW, mess);
}

void error(const char *error_message) {
  if(log_level>NONE)
    log_info("ERROR", error_message);
}

void warning(const char *warning_message) {
  if(log_level>WARNING)
    log_info("WARNING", warning_message);
}

void info(const char *info_message) {
  if(log_level>ERROR) {
    printf("[INFO]: %s\n", info_message);
  }
}

void debug(const char *debug_message) {
  if(log_level>ERROR) {
    printf("[INFO]: %s\n", debug_message);
  }
}
