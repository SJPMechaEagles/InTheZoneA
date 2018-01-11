#include "controller.h"

typedef struct routine_t {
  button_t on_button;
  button_t* blocked_buttons;
  void(*routine)();
}routine_t;

void init_routine();

void routine_task();

void deinit_routines();

void register_routine(void(*routine)(), button_t on_buttons, button_t* prohibited_buttons);
