#include "slew.h"
#include "log.h"

static Mutex mutex;

static int motors_set_speeds[11];
static int motors_curr_speeds[11];

static TaskHandle slew = NULL; //TaskHandle is of type void*

static bool initialized = false;

void updateMotors(){
  //Take back half approach
  //Not linear but equal to setSpeed(1-(1/2)^x)
  for(unsigned int i = 0; i < 11; i++) {
    mutexTake(mutex, 10);
    int set_speed = (motors_set_speeds[i]);
    int curr_speed = motors_curr_speeds[i];
    mutexGive(mutex);
    int diff = set_speed - curr_speed;
    int offset = diff > 0 ? (int)ceil((diff)/4) : (int)floor((diff)/4);
    int n = curr_speed + offset;
    motors_curr_speeds[i+1] = n;
    motorSet(i+1, n);
  }
}

void init_slew(){
  for(int i = 0; i < 11; i++) {
    motors_set_speeds[i] = 0;
    motors_curr_speeds[i] = 0;
    motorSet(i+1, 0);
  }
  printf("Init Slew");
  mutex = mutexCreate();
  slew = taskRunLoop(updateMotors, 40);
  initialized = true;
}



void deinitslew(){
  taskDelete(slew);
}

void set_motor_slew(int motor, int speed){
  mutexTake(mutex, 10);
  motors_set_speeds[motor-1] = speed;
  mutexGive(mutex);
}

void setMotorImmediate(int motor, int speed) {
  motorSet(motor, speed);
  mutexTake(mutex, 10);
  motors_curr_speeds[motor-1] = speed;
  motors_set_speeds[motor-1] = speed;
  mutexGive(mutex);
}
