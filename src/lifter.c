#include "lifter.h"
#include "claw.h"
#include "log.h"
#include "routines.h"
#include "vmath.h"

bool lifter_autostack_running = false;
bool second_pid_enabled = true;
static bool lifter_autostack_routine_interupt = false;
extern Ultrasonic lifter_ultrasonic;

int compare(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

static int lifter_ultra_med(int tests[], int len) {
  qsort(tests, len, sizeof(int), compare);
  if (len % 2 == 0) {
    int med = (tests[len / 2] + tests[len / 2 - 1]) / 2;
    return med;
  }
  int med = tests[len / 2];
  return med;
}

bool main_lifter_should_exit_autostack(int tests_num) {
  int testVals[tests_num];
  for (unsigned int tests = 0; tests < tests_num; tests++) {
    unsigned int ultrasonic_value = ultrasonicGet(lifter_ultrasonic);
    if (ultrasonic_value == ULTRA_BAD_RESPONSE) {
      tests--;
      continue;
    }
    testVals[tests] = ultrasonic_value;
  }
  int median = lifter_ultra_med(testVals, tests_num);
  printf("Median: %d\n", median);
  return abs(median - 19) < 5;
}
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
  // Lift main lifter
  do {
    second_pid_enabled = false;
    raise_secondary_lifter();
    if (lifter_autostack_routine_interupt) {
      quit_auto_static();
      return;
    }
    delay(50);
  } while (analogRead(SECONDARY_LIFTER_POT_PORT) > 3900);
  set_secondary_lifter_motors(0);
  const int target = 3550;
  for (;;) {
    raise_main_lifter();
    if (lifter_autostack_routine_interupt) {
      quit_auto_static();
      return;
    }
    if (main_lifter_should_exit_autostack(3)) {
      break;
    }
  }
  set_main_lifter_motors(0);
  set_secondary_lifter_motors(0);
  unsigned const long start = millis();
  unsigned long time = 0;
  // Lift secondary lifter
  do {
    if (lifter_autostack_routine_interupt) {
      quit_auto_static();
      return;
    }
    raise_secondary_lifter();
    delay(10);
    time = millis();
  } while (((time - start) / 1000.0) < 1);

  lower_main_lifter();
  delay(200);
  set_main_lifter_motors(0);

  // at top
  set_secondary_lifter_motors(0);
  set_main_lifter_motors(0);
  delay(70);
  set_secondary_lifter_motors(0);

  if (lifter_autostack_routine_interupt) {
    quit_auto_static();
    return;
  }
  // release cone
  delay(200);
  set_main_lifter_motors(0);
  claw_release_cone();
  if (lifter_autostack_routine_interupt) {
    quit_auto_static();
    return;
  }
  delay(600);
  set_claw_motor(0);
  set_secondary_lifter_motors(0);

  // get out of way of the cone
  raise_main_lifter();
  delay(200);
  set_main_lifter_motors(0);
  lower_secondary_lifter();
  delay(200);

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
  set_motor_immediate(MOTOR_SECONDARY_LIFTER_LEFT, -v);
  set_motor_immediate(MOTOR_SECONDARY_LIFTER_RIGHT, v);
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
  set_motor_immediate(MOTOR_MAIN_LIFTER_LEFT, v);
  set_motor_immediate(MOTOR_MAIN_LIFTER_RIGHT, v);
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
void lower_main_lifter() { set_main_lifter_motors(MIN_SPEED); }

/**
 * @brief Raises or lowers the main lifter to a until a set
 * height (potentiometer tick)
 *
 * @author Fred Lu
 * @date 4/10/2018
 **/
void move_main_lifter_to(int targetTick) {
  bool direction = 1; //raises lifter by default
  if (getLifterTicks() >= targetTick) {
    //sets the direction to lowering the lifter if lifter is higher than desired height
    direction = 0;
  }
  int initialTick = getLifterTicks();
  int targetDifference = abs(targetTick - initialTick);
  while(abs(getLifterTicks() - initialTick) < targetDifference) {
    if(direction) {
      set_main_lifter_motors(MAX_SPEED);
    } else {
      set_main_lifter_motors(MIN_SPEED);
    }
  }
  set_main_lifter_motors(0);
}

/**
 * @brief Raises the main lifter
 *
 * @author Christian DeSimone
 * @date 9/12/2017
 **/
void raise_secondary_lifter() { set_secondary_lifter_motors(MAX_SPEED); }

/**
 * @brief Lowers the secondary lifter
 *
 * @author Christian DeSimone
 * @date 9/12/2017
 **/
void lower_secondary_lifter() { set_secondary_lifter_motors(MIN_SPEED); }

/**
 * @brief Raises or lowers the secondary lifter to a until a set
 * height (potentiometer tick)
 *
 * @author Fred Lu
 * @date 4/10/2018
 **/
void move_secondary_lifter_to(int tick) {

}

static bool secondary_override = false;

static void main_lifter_update() {
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
  second_motor_speed = 0;
  if (joystickGetDigital(SECONDARY_LIFTER_DOWN)) {
    second_motor_speed = MIN_SPEED;
    claw_grab_cone();
  } else if (joystickGetDigital(SECONDARY_LIFTER_UP)) {
    second_motor_speed = MAX_SPEED;
  } else {
    second_target = second_target > 3000 ? 4095 : second_target;
  }
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
  return (-.0203 * ticks + 52.241);
}
