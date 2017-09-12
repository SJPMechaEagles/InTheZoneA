#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define UPDATE_PERIOD_MS 25
#define RAMP_FACTOR 2

static int *motors_set_speeds = NULL;
// Represents the getMotor function values
static int *curr = NULL;
static unsigned int num_motors = 0;
static unsigned int *increment = NULL;

static void updateMotors(){
  //Take back half approach
  //Not linear but equal to setSpeed(1-(1/2)^x)
  for(unsigned int i = 0; i < num_motors; i++) {
    int set_speed = motors_set_speeds[i];
    int curr_speed = curr[i];
    int diff = set_speed - curr_speed;
    curr[i] = curr_speed + (int)ceil((diff/(float)(RAMP_FACTOR)));
    printf("curr: %d\n", curr_speed);
    printf("set: %d\n", set_speed);
    printf("diff: %d\n\n", diff);
  }
}

void initslew(const int nummotors){
  motors_set_speeds = (int*) calloc(sizeof(int), nummotors);
  curr = (int*) calloc(sizeof(int), nummotors);
  curr[0] = 0;
  increment = (unsigned int*) calloc(sizeof(unsigned int), nummotors);
  num_motors = nummotors;
}

void deinitslew(){
  free(motors_set_speeds);
  free(increment);
}



int main() {
  initslew(1);
  printf("\n");
  motors_set_speeds[0] = 127;
  curr[0] = -127;
  for(int i = 0;; i++) {
    printf("number: %d\n", i);
    updateMotors();
    usleep(100000);
  }
}
