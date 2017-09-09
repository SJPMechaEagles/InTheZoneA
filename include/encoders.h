#ifndef _ENCODERS_H_
#define  _ENCODERS_H_

#include <API.h>

#define IME_NUMBER 1

bool init_encoders() {
  return imeInitializeAll() == IME_NUMBER;
}

#endif
