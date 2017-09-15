#include "drive.h"
#include "ports.h"
#include "vmath.h"
#include "controller.h"
#include <API.h>

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

void updateDriveMotors(){
  struct polar_cord cord = cartesian_cord_to_polar(get_joystick_cord(RIGHT_JOY, MASTER));
}
