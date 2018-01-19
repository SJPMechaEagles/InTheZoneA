#ifndef _GYRO_H_
#define _GYRO_H_

#include "API.h"

/**
 * @brief Port the Gyroscope plugs into.
 */
#define GYRO_PORT 1

/**
 * Special Gyro multiplier for tuning in Gyro
 * @todo
 */
#define GYRO_MULTIPLIER 0

/**
 * @brief Initializes the main robot gryoscope/
 * Only call function when robot still and ready to start autonomous. Robot should not move for five seconds while Gyro
 * calibrates
 * @return if the Gyro was sucessfully calibrated
 * @date 11/30/17
 * @author Chris Jerrett
 */
bool init_main_gyro();

/**
 *  @brief Gets the Gyro angular velocity.
 *  @todo
 *  @return the angular velocity
 *  @author Chris Jerrett
 *  @date 11/30/17
 */
float get_main_gyro_angluar_velocity();

#endif
