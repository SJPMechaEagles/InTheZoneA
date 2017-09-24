#include "slew.h"
#include "log.h"

static Mutex mutex;

static signed char motors_set_speeds[MOTOR_PORTS] = {0};

static TaskHandle slew = NULL; //TaskHandle is of type void*


static bool initialized = false;

void updateMotors(){
  if(isEnabled() && !isAutonomous()) {
    //Take back half approach
    //Not linear but equal to setSpeed(1-(1/2)^x)
    if(mutexTake(mutex, 10)) {
      for(unsigned char i = 0; i < MOTOR_PORTS; i++) {
        char set_speed = motors_set_speeds[i];
        char curr_speed = motorGet(i);
        char diff = set_speed - curr_speed;
        int n = (int) curr_speed + (int) ceil(diff/2);
        motorSet(i, n);
      }
      mutexGive(mutex);
    }
  }
}

void init_slew(){
  info("Init Slew");
  if(motors_set_speeds == NULL) {
    debug("MOTORS SETS NULL!");
  }
  mutex = mutexCreate();
  slew = taskRunLoop(updateMotors, UPDATE_PERIOD_MS);
  initialized = true;
}



void deinitslew(){
  taskDelete(slew);
}

void set_motor_slew(int motor, char speed){
  if(mutexTake(mutex, 100)) {
      motors_set_speeds[motor] = speed;
      mutexGive(mutex);
  }
}
