/**
* @file localization.h
* @author Chris Jerrett, Christian Desimone
* @date 9/27/2017
* @brief Declarations and macros for determining the location of the robot. [WIP]
**/
#ifndef _LOCALIZATION_H_
#define _LOCALIZATION_H_

#include <API.h>
#include "encoders.h"
#include <math.h>
#include "matrix.h"

/**
* How often the localization code updates the position.
**/
#define LOCALIZATION_UPDATE_PERIOD 0.500

/**
* Vector storing the cartesian cords and an angle
**/
struct location {
  int x;
  int y;
  int theta;
};

/**
* @brief Starts the localization process.
* @author Chris Jerrett
*
* @param gyro1 The first gyro
* @prama The multiplier parameter can tune the gyro to adapt to specific sensors.
* The default value at this time is 196; higher values will increase the number of
* degrees reported for a fixed actual rotation, while lower values will decrease the number of
* degrees reported. If your robot is consistently turning too far, increase the multiplier,
* and if it is not turning far enough, decrease the multiplier.
**/
bool init_localization(const unsigned char gyro1, unsigned short multiplier, int start_x, int start_y, int start_theta);

/**
* @brief Gets the current posituion of the robot
*
* @param gyro1 The first gyro
* @return the loacation of the robot as a struct.
**/
struct location get_position();

#endif
