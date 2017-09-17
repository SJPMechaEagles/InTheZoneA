#include "encoders.h"
#include <API.h>

bool init_encoders() {
  #ifdef IME_NUMBER
  return imeInitializeAll() == IME_NUMBER;
  #else
  return imeInitializeAll();
  #endif
}

int get_encoder_ticks(unsigned char address) {
  int i = 0;
  imeGet(address, &i);
  return i;
}

int get_encoder_velocity(unsigned char address) {
  int i = 0;
  imeGetVelocity(address, &i);
  return i;
}
