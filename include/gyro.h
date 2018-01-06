#ifndef _GYRO_H_
#define _GYRO_H_

#include "API.h"

#define GYRO_PORT 1
#define GYRO_MULTIPLIER 0

bool init_main_gyro();
float get_main_gyro_angluar_velocity();

#endif
