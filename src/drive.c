#include "drive.h"
#include "motor_ports.h"
#include "vmath.h"
#include "controller.h"
#include "slew.h"
#include "controller.h"
#include <API.h>
#include "log.h"

static float joystickExp(int joystickVal);

void update_drive_motors(){

  static bool partner = false;
  if(joystickGetDigital(PARTNER, 7, JOY_LEFT)) {
    partner = false;
  } else if(joystickGetDigital(PARTNER, 7, JOY_RIGHT)) {
    partner = true;
  }
  int x = 0;
  int y = 0;
  if(partner) {
    x = (joystickGetAnalog(PARTNER, 4));
    y = (joystickGetAnalog(PARTNER, 2));
  } else {
    x = -(joystickGetAnalog(MASTER, 4));
    y = (joystickGetAnalog(MASTER, 2));
  }

  x = joystickExp(x);
  y = joystickExp(y);

  int r = (x + y);
  int l = -(x - y);

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
    set_motor_slew(MOTOR_MIDDLE_LEFT, speed);
    set_motor_slew(MOTOR_FRONT_LEFT, speed);
  }
}

/**
* @brief Applies exponential scale to a joystick value.
* @author Christian DeSimone, Chris Jerrett
* @param joystickVal the analog value from the joystick
* @date 9/21/2017
**/
static float joystickExp(int joystickVal) {
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
