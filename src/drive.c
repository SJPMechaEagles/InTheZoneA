#include "drive.h"
#include "controller.h"
#include "log.h"
#include "motor_ports.h"
#include "slew.h"
#include "vmath.h"
#include <API.h>

static int thresh = 10;

/**
 * @brief Gets the deadzone threshhold on the drive.
 * @author Christian Desimone
 **/
int getThresh() { return thresh; }

/**
 * @brief Sets the deadzone threshhold on the drive.
 * @author Christian Desimone
 **/
void setThresh(int t) { thresh = t; }

/**
 * @brief Updates the drive motors during teleop
 * @author Christian Desimone
 * @date 9/5/17
 **/
void update_drive_motors() {
  // Get the joystick values from the controller
  int x = 0;
  int y = 0;
	x = -(joystickGetAnalog(MASTER, 3));
	y = (joystickGetAnalog(MASTER, 1));
  // Make sure the joystick values are significant enough to change the motors
  if (x < thresh && x > -thresh) {
    x = 0;
  }
  if (y < thresh && y > -thresh) {
    y = 0;
  }
  // Create motor values for the left and right from the x and y of the joystick
  int r = (x + y);
  int l = -(x - y);

  // Set the drive motors
  set_side_speed(LEFT, l);
  set_side_speed(RIGHT, -r);
}

/**
 * @brief sets the speed of one side of the robot.
 * @author Christian Desimone
 * @param side a side enum which indicates the size.
 * @param speed the speed of the side. Can range from -127 - 127 negative being
 *back and positive forwards
 **/
void set_side_speed(side_t side, int speed) {
  if (side == RIGHT || side == BOTH) {
    set_motor_slew(MOTOR_BACK_RIGHT, -speed);
    set_motor_slew(MOTOR_FRONT_RIGHT, -speed);
    set_motor_slew(MOTOR_MIDDLE_RIGHT, -speed);
  }
  if (side == LEFT || side == BOTH) {
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
  // make the offset negative if moving backwards
  if (abs(joystickVal) < THRESHOLD) {
    return 0;
  }

  int offset;
  // Use the threshold to ensure the joystick values are significant
  if (joystickVal < 0) {
    offset = -(THRESHOLD);
  } else {
    offset = THRESHOLD;
  }
  // Apply the function ((((x/10)^3)/18) + offset) * 0.8 to the joystick value
  return (pow(joystickVal / 10, 3) / 18 + offset) * 0.8;
}
