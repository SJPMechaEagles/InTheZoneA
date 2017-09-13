#include <API.h>
#include <math.h>
#include "log.h"

#define UPDATE_PERIOD_MS 25
#define MOTOR_PORTS 12
#define RAMP_PROPORTION 2

static unsigned char *motors_set_speeds = NULL;
static TaskHandle slew = NULL; //TaskHandle is of type void*
static bool initialized = false;

static void updateMotors(){
  //Take back half approach
  //Not linear but equal to setSpeed(1-(1/2)^x)
  for(int i = 0; i < MOTOR_PORTS; i++) {
    char set_speed = motors_set_speeds[i];
    char curr_speed = motorGet(i);
    char diff = set_speed - curr_speed;
    motorSet(i, curr_speed+ceil(diff/(float)RAMP_PROPORTION));
  }
}

void initslew(){
  motors_set_speeds = (unsigned char*) malloc(sizeof(unsigned char) * MOTOR_PORTS);
  slew = taskRunLoop(updateMotors, UPDATE_PERIOD_MS);
  initialized = true;
}

void deinitslew(){
  free(motors_set_speeds);
  taskDelete(slew);
}

void setMotorS(int motor, int speed){
  motors_set_speeds[motor] = speed;
}
