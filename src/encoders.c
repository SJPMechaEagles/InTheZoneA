#include "encoders.h"
#include "log.h"
#include <API.h>

static bool encoders_initialized = false;

/**
 * @brief Initializes all motor encoders
 * @author Chris Jerrett
 * @date 9/9/2017
 * @see IME_NUMBER
 **/
bool init_encoders() {
  if (encoders_initialized)
    return true;
#ifdef IME_NUMBER
  int count = imeInitializeAll();
  delay(1000);
  if (count != IME_NUMBER) {
    printf("detected only %d\n", count);
    error("Wrong Number of IMEs Connected");
    return false;
  }
  encoders_initialized = true;
  return true;
#else
  return imeInitializeAll();
#endif
}

/**
 * @brief Gets the encoder ticks since last reset
 * @author Chris Jerrett
 * @date 9/15/2017
 **/
int get_encoder_ticks(const unsigned char address) {
  int i = 0;
  imeGet(address, &i);
  return i;
}

/**
 * @brief Gets the encoder reads
 * @author Chris Jerrett
 * @date 9/15/2017
 **/
int get_encoder_velocity(const unsigned char address) {
  int i = 0;
  imeGetVelocity(address, &i);
  return i;
}
