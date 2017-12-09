#include "controller.h"

/**
* @brief Gets the location of a joystick on the controller
* @author Chris Jerrett
**/
struct cord get_joystick_cord(enum joystick side, int controller) {
  int x;
  int y;
  //Get the joystick value for either the right or left,
  //depending on the mode
  if(side == RIGHT_JOY) {
    y = joystickGetAnalog(controller, RIGHT_JOY_X);
    x = joystickGetAnalog(controller, RIGHT_JOY_Y);
  } else {
    y = joystickGetAnalog(controller, LEFT_JOY_X);
    x = joystickGetAnalog(controller, LEFT_JOY_Y);
  }
  //Define a coordinate for the joystick value
  struct cord c;
  c.x = x;
  c.y = y;
  return c;
}
