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

void gyroTurn(int degrees, int minPower, int defaultSpeed) {
  int direction;
  // postive direction means turning right (posiive degrees)
  if (degrees > 0) {
    direction = 1;
  } else {
    direction = -1;
  }
  degrees -= degrees / 20;
  int initial = gyroGet(main_gyro);
  int slowDown = 0;
  int powerLeft;
  int powerRight;
  // turn while the difference is less than the target degrees
  while (abs(initial - gyroGet(main_gyro)) <= abs(degrees)) {
    // if less than 38 degs to target, slow down
    int degsRemaining = abs(degrees) - abs(initial - gyroGet(main_gyro));
    if (degsRemaining <= 38) {
      // slow down by a fraction of degrees remaining;
      slowDown += degsRemaining / 3;
    }
    powerLeft = max(minPower, defaultSpeed - slowDown) * direction;
    powerRight = -max(minPower, defaultSpeed - slowDown) * direction;
    set_side_speed(LEFT, powerLeft);
    set_side_speed(RIGHT, powerRight);

    wait(20);
  }
  delay(500);
  int error = (initial - gyroGet(main_gyro)) - abs(degrees);
  set_side_speed(BOTH, 0);
  return;
}
