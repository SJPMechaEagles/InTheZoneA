#ifndef _PARTNER_H_
#define  _PARTNER_H_

#include "controller.h"
#include "API.h"

enum CONTROLL_MODE {
  MAIN_CONTROLLER_MODE,
  PARTNER_CONTROLLER_MODE
};

void update_control();

enum CONTROLL_MODE get_mode();

#endif
