#ifndef _PARTNER_H_
#define  _PARTNER_H_

#include "controller.h"

enum CONTROLL_MODE {
  MAIN_CONTROLLER_MODE,
  PARTNER_CONTROLLER_MODE
};

enum CONTROLL_MODE current_mode = MAIN_CONTROLLER_MODE;

void update_control();

enum CONTROLL_MODE get_mode();

#endif
