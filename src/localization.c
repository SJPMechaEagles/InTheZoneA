#include "localization.h"

static Gyro g1;
static TaskHandle localization_task;

static int x;
static int y;
static int theta;

static double calculate_angle();

struct location get_position() {

}

void update_position() {
  //int curr_theta = calculate_angle();
  int l = 1;
  int vr = get_encoder_velocity(1);
  int vl = get_encoder_velocity(2);
  int theta_dot = (vr - vl) / l;
  int curr_theta = theta + theta_dot;
  double dt = .005;
  double v_tot = (vr+vl)/2.0;
  int x_curr = x - v_tot*dt*sin(curr_theta);
  int y_curr = y + v_tot*dt*cos(curr_theta);
  x = x_curr;
  y = y_curr;
}

static double calculate_angle() {
  int r1 = gyroGet(g1);
  return r1;
}

bool init_localization(const unsigned char gyro1, unsigned short multiplier, int start_x, int start_y, int start_theta)  {
  g1 = gyroInit(gyro1, multiplier);
  x = start_x;
  y = start_y;
  theta = start_theta;
  localization_task = taskRunLoop(update_position, 5);
  return true;
}
