#include "drive.h"
#include "controller.h"
#include "encoders.h"
#include "motor_ports.h"
#include "slew.h"

static float joystickExp(int joystickVal);

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
  if (x < THRESHOLD && x > -THRESHOLD) {
    x = 0;
  }
  if (y < THRESHOLD && y > -THRESHOLD) {
    y = 0;
  }
  // Create motor values for the left and right from the x and y of the joystick
  int r = (x + y);
  int l = -(x - y);

  r = -joystickExp(r);
  l = joystickExp(l);
  // Set the drive motors

  set_side_speed(LEFT, l);
  set_side_speed(RIGHT, r);
}

/**
 * @brief sets the speed of one side of the robot.
 * @author Christian Desimone
 * @param side a side enum which indicates the size.
 * @param speed the speed of the side. Can range from -127 - 127 negative being
 *		  back and positive forwards
 **/
void set_side_speed(const side_t side, const int speed) {
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
  if (joystickVal > 0) {
    return 129.951 / (1 + K * exp(-(D * (joystickVal + B))));
  }
  return -129.951 / (1 + K * exp(-(D * (-joystickVal + B))));
}

static float ticksToDistance(int ticks) {
  float rotations = ticks / 392.0;
  return rotations * 2 * M_PI * 2.00;
}

void driveStraightDistance(float distance, int speed,
                           void (*functionPtr)(int)) {
  int start_right = (ime_get_right_dist());
  int start_left = (ime_get_left_dist());
  unsigned long start_time = millis();
  float distanceTraveled =
      ticksToDistance((abs(start_left) + abs(start_right)) / 2.00);
  do {
    distanceTraveled =
        ticksToDistance((abs(ime_get_right_dist() - start_right) +
                         abs(ime_get_left_dist() - start_left)) /
                        2.00);
    if (functionPtr != NULL)
      functionPtr(distanceTraveled);
    set_side_speed(RIGHT, speed);
    set_side_speed(LEFT, speed);
    delay(10);
  } while (distanceTraveled < distance - 10);
  set_side_speed(BOTH, 0);
}
