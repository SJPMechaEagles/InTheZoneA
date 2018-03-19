#include "encoders.h"
#include "auto.h"
#include "drive.h"
#include "log.h"
#include "sensors.h"
#include <API.h>

static bool encoders_initialized = false;

int ime_get_right_dist() {
  int front = 0;
  int back = 0;
  // TODO change for new robot
  front = get_encoder_ticks(MID_RIGHT_DRIVE);
  return front;
}

int ime_get_left_dist() {
  int front = 0;
  int back = 0;
  // TODO change for new robot
  front = get_encoder_ticks(MID_LEFT_DRIVE);
  return front;
}

int ime_get_right_vel() {
  int front = 0;
  int back = 0;
  // TODO change for new robot
  front = get_encoder_velocity(MID_RIGHT_DRIVE);
  return front;
}

int ime_get_left_vel() {
  int front = 0;
  int back = 0;
  // TODO change for new robot
  front = get_encoder_velocity(MID_LEFT_DRIVE);
  return front;
}

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
