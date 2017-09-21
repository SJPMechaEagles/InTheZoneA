#include "slew.h"
#include "log.h"

static Mutex mutex;


static signed char *motors_set_speeds = NULL;

static TaskHandle slew = NULL; //TaskHandle is of type void*


static bool initialized = false;

void updateMotors(){
  //Take back half approach
  //Not linear but equal to setSpeed(1-(1/2)^x)
  if(mutexTake(mutex, 10)) {
    for(int i = 0; i < MOTOR_PORTS; i++) {
      char set_speed = motors_set_speeds[i];
      char curr_speed = motorGet(i);
      char diff = set_speed - curr_speed;
      int n = (int) curr_speed + ceil(diff/(float)RAMP_PROPORTION);
      char c[16];
      sprintf(c, "Set Motor %d: %d", i, n);
      debug(c);
      motorSet(i, n);
    }
    mutexGive(mutex);
  }
}

void init_slew(){
  info("Init Slew");
  calloc_real(MOTOR_PORTS, sizeof(char));
  mutex = mutexCreate();
  slew = taskRunLoop(updateMotors, UPDATE_PERIOD_MS);
  initialized = true;
}



void deinitslew(){
  free(motors_set_speeds);
  taskDelete(slew);
}

void set_motor_slew(int motor, int speed){
  if(mutexTake(mutex, 100)) {
      motors_set_speeds[motor] = speed;
      mutexGive(mutex);
  }
}
