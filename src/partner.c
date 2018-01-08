#include "partner.h"

static enum CONTROLL_MODE mode = MAIN_CONTROLLER_MODE;

enum CONTROLL_MODE get_mode() { return mode; }

void update_control() {
  if (joystickGetDigital(PARTNER, 7, JOY_LEFT)) {
    mode = MAIN_CONTROLLER_MODE;
  } else if (joystickGetDigital(PARTNER, 7, JOY_RIGHT)) {
    mode = PARTNER_CONTROLLER_MODE;
  }
}
