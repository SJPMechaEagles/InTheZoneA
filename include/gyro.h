/**
 * @file gyri.h
 * @brief Declarations and macros for the VEX gyroscope.
 * @author Chris Jerrett, Christian Desimone
 */
#ifndef _GYRO_H_
#define _GYRO_H_

#include "API.h"
#include "drive.h"

/**
 * @brief Port the Gyroscope plugs into.
 */
#define GYRO_PORT 1

/**
 * Special Gyro multiplier for tuning in Gyro
 * @todo
 */
#define GYRO_MULTIPLIER 196
#define GYRO_TURN_SPEED_MAX 80
#define GYRO_TURN_SPEED_MIN_NORMAL 34
#define GYRO_TURN_SPEED_MIN_FAST 48

/**
 * @brief Initializes the main robot gryoscope/
 * Only call function when robot still and ready to start autonomous. Robot
 * should not move for five seconds while Gyro calibrates
 * @return if the Gyro was successfully calibrated
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
