#include "drive.h"

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
  float degree = 0;
  int magnitude = sqrt((abs(x) * abs(x)) + (abs(y) * abs(y)));

  if( x < 0){
    degree += 180.0;
  }
  else if( x > 0 && y < 0){
    degree += 360.0;
  }

  if( x != 0 && y != 0){
    degree += atan((float)y / (float)x);
  }
  else if(x == 0 && y > 0){
    degree = 90.0;
  }
  else if(y == 0 && x < 0){
    degree = 180.0;
  }
  else if(x == 0 && y < 0){
    degree = 270.0;
  }
}
