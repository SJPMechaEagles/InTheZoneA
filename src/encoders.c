#include "encoders.h"
#include <API.h>

/**
* @brief Initializes all motor encoders
* @author Chris Jerrett
* @date 9/9/2017
* @see IME_NUMBER
**/
bool init_encoders() {
  #ifdef IME_NUMBER
  return imeInitializeAll() == IME_NUMBER;
  #else
  return imeInitializeAll();
  #endif
}

/**
* @brief Gets the encoder ticks since last reset
* @author Chris Jerrett
* @date 9/15/2017
**/
int get_encoder_ticks(unsigned char address) {
  int i = 0;
  imeGet(address, &i);
  return i;
}

/**
* @brief Gets the encoder reads
* @author Chris Jerrett
* @date 9/15/2017
**/
int get_encoder_velocity(unsigned char address) {
  int i = 0;
  imeGetVelocity(address, &i);
  return i;
}
