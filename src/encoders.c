#include "encoders.h"
#include "auto.h"
#include "drive.h"
#include "log.h"
#include "sensors.h"
#include <API.h>

static bool encoders_initialized = false;

void zero_imes() {
  for (int i = 0; i < IME_NUMBER; i++) {
    imeReset(i);
  }
}

int ime_get_average(bool multi) {
  //use the first connected encoder
  int avg = 0;
  if (multi) {
    avg = (abs(ime_get_right_dist()) + abs(ime_get_left_dist())) / 2;
  } else {
    avg = get_encoder_ticks(BACK_RIGHT_IME);
  }
  return avg;
}

int ime_get_right_dist() {
  int front = 0;
  int back = 0;
  // TODO change for new robo
  back = get_encoder_ticks(BACK_RIGHT_IME);
  front = get_encoder_ticks(FRONT_RIGHT_IME);
  return (int) (.5 * (front + back));
}

int ime_get_left_dist() {
  int back = 0;
  int front = 0;
  // TODO change for new robot
  back = get_encoder_ticks(FRONT_LEFT_IME);
  front = get_encoder_ticks(FRONT_RIGHT_IME);
  return (int)(.5 * (front + back));
}

int ime_get_right_vel() {
  int front = 0;
  int back = 0;
  front = get_encoder_velocity(FRONT_RIGHT_IME);
  back = get_encoder_velocity(BACK_RIGHT_IME);
  return (front + back) / 2;
}

int ime_get_left_vel() {
  int front = 0;
  int back = 0;
  front = get_encoder_velocity(FRONT_LEFT_IME);
  back = get_encoder_velocity(BACK_LEFT_IME);
  return (front + back) / 2;
}

/**
 * @brief Initializes all motor encoders
 * @author Chris Jerrett
 * @date 9/9/2017
 * @see IME_NUMBER
 **/
bool init_encoders() {
#ifdef IME_NUMBER
  int count = imeInitializeAll();
  if (count != IME_NUMBER) {
    printf("detected only %d\n", count);
    error("Wrong Number of IMEs Connected");
    imeReset(0);
    return false;
  }
  imeReset(0);
  imeReset(1);
  imeReset(2);
  imeReset(3);
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
