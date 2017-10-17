#include "slew.h"
#include "log.h"

static Mutex mutex;

static int motors_set_speeds[12];
static int motors_curr_speeds[12];

static TaskHandle slew = NULL; //TaskHandle is of type void*

static bool initialized = false;

void updateMotors(){
  //Take back half approach
  //Not linear but equal to setSpeed(1-(1/2)^x)
  for(unsigned int i = 0; i < 12; i++) {
    mutexTake(mutex, 10);
    int set_speed = (motors_set_speeds[i]);
    int curr_speed = motors_curr_speeds[i];
    mutexGive(mutex);
    int diff = set_speed - curr_speed;
    int offset = diff > 0 ? (int)ceil((diff)/4) : (int)floor((diff)/4);
    int n = curr_speed + offset;
    motors_curr_speeds[i] = n;
    printf("Port: %d, Set: %d Curr: %d Diff %d New: %d\n", i, set_speed, curr_speed, diff, n);
    motorSet(i, n);
  }
}

void init_slew(){
  for(int i = 0; i < 12; i++) {
    motors_set_speeds[i] = 0;
    motors_curr_speeds[i] = 0;
    motorSet(i, 0);
  }
  printf("Init Slew");
  mutex = mutexCreate();
  slew = taskRunLoop(updateMotors, 100);
  initialized = true;
}



void deinitslew(){
  taskDelete(slew);
}

void set_motor_slew(int motor, int speed){
  mutexTake(mutex, 10);
  motors_set_speeds[motor] = speed;
  mutexGive(mutex);
}

void setMotorImmediate(int motor, int speed) {
  motorSet(motor, speed);
  mutexTake(mutex, 10);
  motors_curr_speeds[motor] = speed;
  motors_set_speeds[motor] = speed;
  mutexGive(mutex);
}
