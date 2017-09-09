/**
* @file drive.h
* @author Christian Desimone
* @date 9/9/2017
* @brief Drive base definitions and eumerations
**/

#ifndef _DRIVE_H_
#define _DRIVE_H_

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
* @bried Front right drive motor of robot base
* @author Christian Desimone
* @date 9/7/2017
**/
#define MOTOR_FRONT_RIGHT 0

/**
* @bried Front left drive motor of robot base
* @author Christian Desimone
* @date 9/7/2017
**/
#define MOTOR_FRONT_LEFT 1

/**
* @bried Middle right drive motor of robot base
* @author Christian Desimone
* @date 9/7/2017
**/
#define MOTOR_MIDDLE_RIGHT 2

/**
* @bried Middle left drive motor of robot base
* @date 9/7/2017
* @author Christian Desimone
**/
#define MOTOR_MIDDLE_LEFT 3
/**
* @bried Back right drive motor of robot base
* @author Christian Desimone
* @date 9/7/2017
**/
#define MOTOR_BACK_RIGHT 4
/**
* @bried Back left drive motor of robot base
* @author Christian Desimone
* @date 9/7/2017
**/
#define MOTOR_BACK_LEFT 5

/**
* @bried sets the speed of one side of the robot.
* @author Christian Desimone
* @param side a side enum which indicates the size.
* @param speed the speed of the side. Can range from -127 - 127 negative being back and positive forwards
**/
void set_side_speed(side side, int speed);

void updateDriveMotors();
#endif
