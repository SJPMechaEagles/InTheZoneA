#include "drive.h"
#include <math.h>
#include <API.h>
#include "controller.h"
#include "vmath.h"

/**
* @bried sets the speed of one side of the robot.
* @author Christian Desimone
* @param side a side enum which indicates the size.
* @param speed the speed of the side. Can range from -127 - 127 negative being back and positive forwards
**/
void set_side_speed(side side, int speed){
  if(side == right || side == both){
    motorSet(MOTOR_BACK_RIGHT , speed);
    motorSet(MOTOR_FRONT_RIGHT, speed);
    motorSet(MOTOR_MIDDLE_RIGHT, speed);
  }
  if(side == left || side == both){
    motorSet(MOTOR_BACK_LEFT, speed);
    motorSet(MOTOR_BACK_LEFT, speed);
    motorSet(MOTOR_BACK_LEFT, speed);
  }
}

/**
* @bried Updates the drive motosrs during teleop
* @author Christian Desimone
* @date 9/5/17
**/
void updateDriveMotors(){
  int y = joystickGetAnalog(MASTER, RIGHT_JOY_X);
  int x = joystickGetAnalog(MASTER, RIGHT_JOY_Y);
  struct polar_cord cord = cartesian_to_polar((float) x, (float) y);
}
