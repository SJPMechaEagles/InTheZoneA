#include "drive.h"
#include "motor_ports.h"
#include "vmath.h"
#include "controller.h"
#include "slew.h"
#include "controller.h"
#include <API.h>
#include "log.h"

void update_drive_motors(){

  int x = (joystickGetAnalog(1, 2));
  int y = (joystickGetAnalog(1, 1));

  int r = (x + y);
  int l = -(x - y);

  printf("x: %d, y: %d\n", x, y);

  set_side_speed(LEFT, l);
  set_side_speed(RIGHT, r);

}

void set_side_speed(side_t side, int speed){
  if(side == RIGHT || side == BOTH){
    set_motor_slew(MOTOR_BACK_RIGHT , speed);
    set_motor_slew(MOTOR_FRONT_RIGHT, speed);
    set_motor_slew(MOTOR_MIDDLE_RIGHT, speed);
  }
  if(side == LEFT || side == BOTH){
    set_motor_slew(MOTOR_BACK_LEFT, speed);
    set_motor_slew(MOTOR_BACK_LEFT, speed);
    set_motor_slew(MOTOR_BACK_LEFT, speed);
  }
}

static int joystick_interpolate(int val) {

}

float joystickExp(int joystickVal) {
	//make the offset negative if moving backwards
	if (abs(joystickVal) < THRESHOLD) {
			return 0;
	}

	int offset;
	if (joystickVal < 0) {
		offset = - (THRESHOLD);
	} else {
		offset = THRESHOLD;
	}


	return (pow(joystickVal/10 , 3) / 18 + offset) * 0.8;
}
