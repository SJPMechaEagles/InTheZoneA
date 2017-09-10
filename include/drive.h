/**
* @file drive.h
* @author Christian Desimone
* @date 9/9/2017
* @brief Drive base definitions and eumerations
**/

#ifndef _DRIVE_H_
#define _DRIVE_H_

#include "ports.h"

/**
* @brief enumeration indication side of the robot.
* @author Christian Desimone
* @date 9/7/2017
* Side can be right, both of left. Containted in side typedef, so enum is unnedcessary.
**/
typedef enum side{
  left,
  both,
  right
} side;

/**
* @bried sets the speed of one side of the robot.
* @author Christian Desimone
* @param side a side enum which indicates the size.
* @param speed the speed of the side. Can range from -127 - 127 negative being back and positive forwards
**/
void set_side_speed(side side, int speed);

/**
* @bried Updates the drive motosrs during teleop
* @author Christian Desimone
* @date 9/5/17
**/
void updateDriveMotors();

#endif
