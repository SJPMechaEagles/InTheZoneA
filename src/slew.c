#include "slew.h"
#include "log.h"

static Mutex mutex;

static signed char motors_set_speeds[12] = {0};

static TaskHandle slew = NULL; //TaskHandle is of type void*

static bool initialized = false;

void updateMotors(){
  //Take back half approach
  //Not linear but equal to setSpeed(1-(1/2)^x)
  for(unsigned char i = 0; i < 12; i++) {
    char set_speed = motors_set_speeds[i];
    char curr_speed = motorGet(i);
    char diff = set_speed - curr_speed;
    int n = (int) curr_speed + (int) ceil(diff/2);
    //printf("Port: %d, Set: %d Curr: %d Diff %d New: %d\n", i, set_speed, curr_speed, diff, n);
    motorSet(i, n);
  }
}

void init_slew(){
  info("Init Slew");
  if(motors_set_speeds == NULL) {
    debug("MOTORS SETS NULL!");
  }
  mutex = mutexCreate();
  slew = taskRunLoop(updateMotors, 20);
  initialized = true;
}



void deinitslew(){
  taskDelete(slew);
}

void set_motor_slew(int motor, char speed){
    motors_set_speeds[motor] = speed;
}
