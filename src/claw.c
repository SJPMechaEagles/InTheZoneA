#include "claw.h"
#include "sensor_ports.h"

void update_claw() {
  static bool changed = true;
  static int target = 0;
  if(joystickGetDigital(MASTER, 8, JOY_RIGHT)){
    changed = true;
    target = getClawTicks();
    close_claw();
  }
  else if(joystickGetDigital(MASTER, 8, JOY_LEFT)) {
    changed = true;
    target = getClawTicks();
    open_claw();
  }
  else {
    static int i = 0;
    if(changed) {
      target = getClawTicks();
      i = 0;
    }
    int p = target - getClawTicks();
    i += p;
    int d = target - getClawTicks();
    int motorVal = -p/10 - d/100 -i/400;
    //printf("%d\n", motorVal);

    set_claw_motor(motorVal);
    changed = false;
  }
}


void set_claw_motor(const char v){
  set_motor_slew(CLAW_MOTOR, v);
}

int getClawTicks(){
  return analogReadCalibrated(CLAW_POT);
}

void open_claw() {
  set_motor_immediate(CLAW_MOTOR, 70);
}

void close_claw() {
  set_motor_immediate(CLAW_MOTOR, -70);
}
