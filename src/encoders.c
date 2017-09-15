#include "encoders.h"

bool init_encoders() {
  return imeInitializeAll() == IME_NUMBER;
}
