#include "slew.h"
#include "log.h"

static Mutex speeds_mutex;

static int motors_set_speeds[10];
static int motors_curr_speeds[10];

static TaskHandle slew = NULL; //TaskHandle is of type void*

static bool initialized = false;

void updateMotors(){
  //Take back half approach
  //Not linear but equal to setSpeed(1-(1/2)^x)
  for(unsigned int i = 0; i < 9; i++) {
    mutexTake(speeds_mutex, 10);
    int set_speed = (motors_set_speeds[i]);
    int curr_speed = motors_curr_speeds[i];
    mutexGive(speeds_mutex);
    int diff = set_speed - curr_speed;
    int offset = diff;
    int n = curr_speed + offset;
    motors_curr_speeds[i] = n;
    motorSet(i+1, n);
  }
}

void init_slew(){
  if(initialized) {
    warning("Trying to init already init slew");
  }
  memset(motors_set_speeds, 0, sizeof(int) * 10);
  memset(motors_curr_speeds, 0, sizeof(int) * 10);
  motorStopAll();
  info("Did Init Slew");
  speeds_mutex = mutexCreate();
  slew = taskRunLoop(updateMotors, 100);
  initialized = true;
}

void deinitslew(){
  taskDelete(slew);
  memset(motors_set_speeds, 0, sizeof(int) * 10);
  memset(motors_curr_speeds, 0, sizeof(int) * 10);
  initialized = false;
}

void set_motor_slew(int motor, int speed){
  if(!initialized) {
    debug("Slew Not Initialized! Initializing");
    init_slew();
  }
  mutexTake(speeds_mutex, 10);
  motors_set_speeds[motor-1] = speed;
  mutexGive(speeds_mutex);
}

void set_motor_immediate(int motor, int speed) {
  if(!initialized) {
    debug("Slew Not Initialized! Initializing");
    init_slew();
  }
  motorSet(motor, speed);
  mutexTake(speeds_mutex, 10);
  motors_curr_speeds[motor-1] = speed;
  motors_set_speeds[motor-1] = speed;
  mutexGive(speeds_mutex);
}
