#include "claw.h"
#include "sensor_ports.h"

void update_claw() {
  static bool pressed_last = true;
  static int target = 0;

  if(joystickGetDigital(MASTER, 8, JOY_RIGHT)) {
    close_claw();
  } else if(joystickGetDigital(MASTER, 8, JOY_LEFT)) {
    open_claw();
  } else {
    int current_pot = analogRead(CLAW_POT);
    static int last = 0;
    if(!pressed_last) {
      target = current_pot;
      last = current_pot;
    }
    static int integral = 0;
    int p = current_pot - target;
    int d = current_pot - last;
    integral+=p;

    int motor_value = p/100 + d/1000 + integral/10000;
    last = current_pot;
    //printf("P: %d I: %d D: %d\n", p/100, d/1000, integral/10000);
    setMotorImmediate(CLAW_MOTOR, -motor_value);
  }
}

void open_claw() {
  setMotorImmediate(CLAW_MOTOR, 70);
}

void close_claw() {
  setMotorImmediate(CLAW_MOTOR, -70);
}
