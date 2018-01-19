#include "gyro.h"

static Gyro main_gyro;
/**
 * @brief Initializes the gyro
 * @author Chris Jerrett
 * @see GYRO_PORT
 * @see GYRO_MULTIPLIER
 **/
bool init_main_gyro() {
  main_gyro = gyroInit(GYRO_PORT, GYRO_MULTIPLIER);
  return main_gyro != NULL;
}

/**
 * @brief returns the angular velocity directly from the gyro
 * @author Chris Jerrett
 * @see GYRO_PORT
 **/
float get_main_gyro_angluar_velocity() {
  uint32_t port = GYRO_PORT;
  int32_t reading = (int32_t)analogReadCalibratedHR(port + 1);
  return 0;
}
