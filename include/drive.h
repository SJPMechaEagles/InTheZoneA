/**
 * @file drive.h
 * @author Chris Jerrett
 * @date 9/9/2017
 * @brief Drive base definitions and enumerations
 **/

#ifndef _DRIVE_H_
#define _DRIVE_H_

#include <API.h>
#include "math.h"
#include "vmath.h"

/**
 * @brief The dead spot on the controller to avoid running motors at low
 * speeds.
 **/
#define THRESHOLD 10

#define D (0.066)

#define B (-110)

#define K (0.05)

#define BASE_P .005
#define BASE_D .0006
#define BASE_I .0000004

/**
 * @brief enumeration indication side of the robot.
 * @author Christian Desimone
 * @date 9/7/2017
 * Side can be right, both of left. Contained in side typedef, so enum is
 *unnecessary.
 **/
typedef enum side { LEFT, BOTH, RIGHT } side_t;

/**
 * @brief sets the speed of one side of the robot.
 * @author Christian Desimone
 * @param side a side enum which indicates the size.
 * @param speed the speed of the side. Can range from -127 - 127 negative being
 *back and positive forwards
 **/
void set_side_speed(const side_t side, const int speed);

void set_side_speed_no_slew(const side_t side, const int speed);

/**
 * @brief Updates the drive motors during teleop
 * @author Christian Desimone
 * @date 9/5/17
 **/
void update_drive_motors();

void driveStraightDistance(float distance, int speed, void (*functionPtr)(int),
                           void (*start_function)(void *));

#endif
