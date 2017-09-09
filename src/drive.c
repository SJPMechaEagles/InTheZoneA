#include "drive.h"
#include <math.h>
#include <API.h>
#include "joystick.h"
#include "vmath.h"

void set_side_speed(side side, int speed){
  if(side != right){
    motorSet(FLEFT , speed);
    motorSet(MLEFT, speed);
    motorSet(BLEFT, speed);
  }
  if(side != left){
    motorSet(FRIGHT, speed);
    motorSet(MRIGHT, speed);
    motorSet(BRIGHT, speed);
  }
}

void updateMotors(){
  int y = joystickGetAnalog(MASTER, RIGHT_JOY_X);
  int x = joystickGetAnalog(MASTER, RIGHT_JOY_Y);
  struct polar_cord cord = cartesian_to_polar((float) x, (float) y);
}
