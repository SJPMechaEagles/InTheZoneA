#include "drive.h"
#include "ports.h"
#include "vmath.h"
#include "controller.h"
#include <API.h>

void set_side_speed(side_t side, int speed){
  if(side == RIGHT || side == BOTH){
    motorSet(MOTOR_BACK_RIGHT , speed);
    motorSet(MOTOR_FRONT_RIGHT, speed);
    motorSet(MOTOR_MIDDLE_RIGHT, speed);
  }
  if(side == LEFT || side == BOTH){
    motorSet(MOTOR_BACK_LEFT, speed);
    motorSet(MOTOR_BACK_LEFT, speed);
    motorSet(MOTOR_BACK_LEFT, speed);
  }
}

static int joystick_interpolate(int val) {

}

static int deadspot(int val) {
  return abs(val) > DEADSPOT ? val : 0;
}

void update_drive_motors(){
  struct polar_cord cord = cartesian_cord_to_polar(get_joystick_cord(RIGHT_JOY, MASTER));
}
