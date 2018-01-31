#include "lifter.h"
#include "claw.h"
#include "log.h"
#include "routines.h"
#include "vmath.h"

bool lifter_autostack_running = false;
static bool lifter_autostack_routine_interupt = false;
extern Ultrasonic lifter_ultrasonic;

/**
 * @brief interupts an autostack routine.
 * @param param the task the interrupt is running on.
 **/
void interrupt_auto_stack(void *param) {
  lifter_autostack_routine_interupt = true;
}

/**
 * @brief call when the autostack can exit to stop the motors.
 **/
static inline void quit_auto_static() {
  set_main_lifter_motors(0);
  set_secondary_lifter_motors(0);
  set_claw_motor(0);
  lifter_autostack_running = false;
}

/**
 * @brief automatically stacks a cone on the stack.
 * @param param the taskt the routine is running in.
 **/
void autostack_routine(void *param) {
  set_claw_motor(0);
  lifter_autostack_routine_interupt = false;
  lifter_autostack_running = true;
  raise_secondary_lifter();
  while (analogRead(SECONDARY_LIFTER_POT_PORT) < 1800) {
    set_secondary_lifter_motors(MIN_SPEED);
    if (lifter_autostack_routine_interupt) {
      quit_auto_static();
      return;
    }
    delay(50);
    info("1");
  }
  set_secondary_lifter_motors(0);
  int val1 = ultrasonicGet(lifter_ultrasonic);
  delay(20);
  int val2 = ultrasonicGet(lifter_ultrasonic);
  printf("%d, %d\n", val1, val2);
  while (min(val1, val2) < 10) {
    raise_main_lifter();
    if (lifter_autostack_routine_interupt) {
      quit_auto_static();
      return;
    }
    val1 = ultrasonicGet(lifter_ultrasonic);
    delay(30);
    val2 = ultrasonicGet(lifter_ultrasonic);
    printf("%d, %d\n", val1, val2);
    delay(30);
  }
  if (lifter_autostack_routine_interupt) {
    quit_auto_static();
    return;
  }
  set_main_lifter_motors(0);
  while (analogRead(SECONDARY_LIFTER_POT_PORT) < 3150) {
    if (lifter_autostack_routine_interupt) {
      quit_auto_static();
      return;
    }
    set_secondary_lifter_motors(MIN_SPEED);
    delay(50);
  }

  set_secondary_lifter_motors(-10);
  set_main_lifter_motors(0);

  if (lifter_autostack_routine_interupt) {
    quit_auto_static();
    return;
  }
  delay(300);
  set_main_lifter_motors(MIN_SPEED);
  delay(200);
  set_main_lifter_motors(0);
  delay(50);
  set_claw_motor(MIN_CLAW_SPEED);
  if (lifter_autostack_routine_interupt) {
    quit_auto_static();
    return;
  }
  delay(500);
  set_claw_motor(0);
  set_secondary_lifter_motors(0);

  raise_main_lifter();
  delay(200);
  set_main_lifter_motors(0);

  lifter_autostack_running = false;
}

/**
 * @brief Sets the secondary lifter motors to the given value
 *
 * @param v value for the lifter motor. Between -128 - 127, any values outside
 *are clamped.
 * @author Chris Jerrett
 * @date 1/6/2018
 **/
void set_secondary_lifter_motors(const int v) {
  set_motor_immediate(MOTOR_SECONDARY_LIFTER, v);
}

/**
 * @brief Sets the main lifter motors to the given value
 *
 * @param v value for the lifter motor. Between -128 - 127, any values outside
 *are clamped.
 * @author Chris Jerrett
 * @date 9/9/2017
 **/
void set_main_lifter_motors(const int v) {
  set_motor_slew(MOTOR_MAIN_LIFTER, v);
}

/**
 * @brief Sets the lifter positions to the given value
 *
 * @param pos The height in inches
 * @author Chris Jerrett
 * @date 9/12/2017
 **/
void set_lifter_pos(int pos) {}

/**
 * @brief Raises the main lifter
 *
 * @author Christian DeSimone
 * @date 9/12/2017
 **/
void raise_main_lifter() { set_main_lifter_motors(MAX_SPEED); }

/**
 * @brief Lowers the main lifter
 *
 * @author Christian DeSimone
 * @date 9/12/2017
 **/
void lower_main_lifter() { set_main_lifter_motors(MAX_SPEED); }

/**
 * @brief Raises the main lifter
 *
 * @author Christian DeSimone
 * @date 9/12/2017
 **/
void raise_secondary_lifter() { set_secondary_lifter_motors(MIN_SPEED / 1.5); }

/**
 * @brief Lowers the secondary lifter
 *
 * @author Christian DeSimone
 * @date 9/12/2017
 **/
void lower_secondary_lifter() { set_secondary_lifter_motors(MAX_SPEED); }

static bool secondary_override = false;

static void main_lifter_update() {
  if (lifter_autostack_running) {
    return;
  }
  static int count = 0;
  static bool pid_on = false;
  static int main_target = 0;
  int main_motor_speed = 0;
  static long long main_i = 0;
  if (count == 20) {
    main_target = analogRead(MAIN_LIFTER_POT);
  }
  if (pid_on && count > 20) {
    int curr = analogRead(MAIN_LIFTER_POT);
    static int main_last_p = 0;
    int main_p = curr - main_target;
    main_i += main_p;
    int main_d = main_last_p - main_p;
    // main_motor_speed = MAIN_LIFTER_P * main_p + MAIN_LIFTER_I * main_i +
    // MAIN_LIFTER_D * main_d;
    main_last_p = main_p;
  } else {
    main_i = 0;
    count++;
  }
  if (joystickGetDigital(LIFTER_UP)) {
    int ultra = ultrasonicGet(lifter_ultrasonic);
    main_motor_speed = MAX_SPEED;
    count = 0;
  } else if (joystickGetDigital(LIFTER_DOWN)) {
    main_motor_speed = MIN_SPEED;
    count = 0;
    secondary_override = false;
  } else {
    secondary_override = false;
  }
  set_main_lifter_motors(main_motor_speed);
  pid_on = true;
}

static void secondary_lifter_update() {
  if (lifter_autostack_running)
    return;
  static int count = 0;
  // static bool pid_on = false;
  static int second_target = 0;
  int second_motor_speed = 0;
  static long long second_i = 0;

  if (count < 10) {
    second_target = analogRead(SECONDARY_LIFTER_POT_PORT);
    count++;
  }

  int curr = analogRead(SECONDARY_LIFTER_POT_PORT);
  static int second_last_p = 0;
  int second_p = curr - second_target;
  second_i += second_p;
  int second_d = second_last_p - second_p;
  second_motor_speed = SECONDARY_LIFTER_P * second_p +
                       SECONDARY_LIFTER_I * second_i +
                       SECONDARY_LIFTER_D * second_d;
  second_last_p = second_p;

  if (joystickGetDigital(SECONDARY_LIFTER_DOWN)) {
    second_motor_speed = MAX_SPEED;
    count = 0;
    second_i = 0;
    second_target = analogRead(SECONDARY_LIFTER_POT_PORT);
    claw_grab_cone();
  } else if (joystickGetDigital(SECONDARY_LIFTER_UP)) {
    second_motor_speed = MIN_SPEED;
    count = 0;
    second_i = 0;
    second_target =
        second_target > 3000 ? 4095 : analogRead(SECONDARY_LIFTER_POT_PORT);
  } else {
    second_target = second_target > 3000 ? 4095 : second_target;
  }
  second_motor_speed = abs(second_motor_speed) < 20 ? 0 : second_motor_speed;
  set_secondary_lifter_motors(second_motor_speed);
}

/**
 * @brief Updates the lifter in teleop.
 *
 * @author Chris Jerrett
 * @date 9/9/2017
 **/
void update_lifter() {
  // printf("%d \n", analogRead(SECONDARY_LIFTER_POT_PORT));
  main_lifter_update();
  if (!secondary_override)
    secondary_lifter_update();
}
/**
 * @brief height of the lifter in degrees from 0 height
 *
 * @param x the pot value
 * @return the positions in degrees
 * @author Chris Jerrett
 * @date 10/13/2017
 **/
float lifterPotentiometerToDegree(int x) {
  return (x - INIT_ROTATION) / TICK_MAX * DEG_MAX;
}

/**
 * @brief Gets the value of the lifter pot.
 *
 * @return the value of the pot.
 * @author Chris Jerrett
 * @date 9/9/2017
 **/
int getLifterTicks() { return analogRead(LIFTER); }

/**
 * @brief Gets the height of the lifter in inches.
 *
 * @return the height of the lifter.
 * @author Chris Jerrett
 * @date 9/17/2017
 **/
double getLifterHeight() {
  unsigned int ticks = getLifterTicks();
  return (-2 * pow(10, (-9 * ticks)) + 6 * (pow(10, (-6 * ticks * ticks))) +
          0.0198 * ticks + 2.3033);
}
