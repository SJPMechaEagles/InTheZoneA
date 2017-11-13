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

  int x = 0;
  int y = 0;
  if(get_mode() == PARTNER_CONTROLLER_MODE) {
    y = (joystickGetAnalog(PARTNER, 3));
    x = (joystickGetAnalog(PARTNER, 1));
  } else {
    x = -(joystickGetAnalog(MASTER, 3));
    y = (joystickGetAnalog(MASTER, 1));
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
