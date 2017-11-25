#ifndef _LOCALIZATION_H_
#define _LOCALIZATION_H_

#include <API.h>
#include "encoders.h"
#include <math.h>
#include "matrix.h"

#define LOCALIZATION_UPDATE_FREQUENCY 0.500

struct location {
  int x;
  int y;
  int theta;
};
/**
* @brief Starts the localization process.
*
* @param gyro1 The first gyro
* @prama The multiplier parameter can tune the gyro to adapt to specific sensors.
* The default value at this time is 196; higher values will increase the number of
* degrees reported for a fixed actual rotation, while lower values will decrease the number of
* degrees reported. If your robot is consistently turning too far, increase the multiplier,
* and if it is not turning far enough, decrease the multiplier.
**/
bool init_localization(const unsigned char gyro1, unsigned short multiplier, int start_x, int start_y, int start_theta);
struct location get_position();

#endif
