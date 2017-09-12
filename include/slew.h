#include <stdio.h>
#include <API.h>

#define UPDATE_PERIOD_MS 25

static unsigned char *motors_set_speeds = NULL;
static int num_motors = 0;
static unsigned char *increment = NULL;
static TaskHandle slew = NULL; //TaskHandle is of type void*

static void updateMotors(){
  //Take back half approach
  //Not linear but equal to setSpeed(1-(1/2)^x)
  for(int i = 0; i < num_motors; i++) {
    char set_speed = motors_set_speeds[i];
    char curr_speed = motorGet(i);
    char diff = set_speed - curr_speed;
    motors_set_speeds[i] += diff/2;
  }
  /*for(int i = 0; i < size; i++){
    if(abs(motors[i] - motorGet(i)) < increment[i]){
      motorSet(i, motorGet(i) + increment[i]);
    }
    else if(motors[i] != motorGet(i)){
      motorSet(i, motors[i]);
    }
  }*/
}

void initslew(int nummotors){
  motors_set_speeds = (unsigned char*) malloc(sizeof(unsigned char) * nummotors);
  increment = (unsigned char*) malloc(sizeof(unsigned char) * nummotors);
  num_motors = nummotors;
  slew = taskRunLoop(updateMotors, UPDATE_PERIOD_MS);
}

void deinitslew(){
  free(motors_set_speeds);
  free(increment);
  taskDelete(slew);
}



void setMotorS(int motor, int speed){
  motors_set_speeds[motor] = speed;
  increment[motor] = (speed - motorGet(motor))/5;
}
