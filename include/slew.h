#include <stdio.h>
#include <API.h>

static unsigned char *motors = NULL;
static int size = 0;
static unsigned char *increment = NULL;
static TaskHandle slew = NULL;

void updateMotors(){
  for(int i = 0; i < size; i++){
    if(abs(motors[i] - motorGet(i)) < increment[i]){
      motorSet(i, motorGet(i) + increment[i]);
    }
    else if(motors[i] != motorGet(i)){
      motorSet(i, motors[i]);
    }
  }
}

void initslew(int nummotors){
  motors = (unsigned char*) malloc(sizeof(unsigned char) * nummotors);
  increment = (unsigned char*) malloc(sizeof(unsigned char) * nummotors);
  size = nummotors;
  slew = taskRunLoop(updateMotors, 10);
}

void deinitslew(){
  taskDelete(slew);
}



void setMotorS(int motor, int speed){
  motors[motor] = speed;
  increment[motor] = (speed - motorGet(motor))/5;
}
