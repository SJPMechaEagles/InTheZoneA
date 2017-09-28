#include "localization.h"

static Gyro g1;
static TaskHandle localization_task;

static double x;
static double y;
static double theta;

struct encoder_odemtry {
  double x;
  double y;
  double theta;
};

struct accelerometer_odometry {
  double x;
  double y;
};

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

static struct accelerometer_odometry calculate_accelerometer_odemetry() {
  double dx_rel = 0;
  double dy_rel = 0;
  double dx_abs = (dy_rel * cos(theta) + dx_rel * sin(theta));
  double dy_abs = (dy_rel * sin(theta) + dx_rel * cos(theta));
  struct accelerometer_odometry odd;
  odd.x = x + dx_abs;
  odd.y = y + dy_abs;
  return odd;
}

static double integrate_gyro_w(int new_w) {
  static double theta = 0;
  double delta_theta = new_w * LOCALIZATION_UPDATE_FREQUENCY;
  theta += delta_theta;
}

static double calculate_gryo_anglular_velocity() {
  static int last_gyro = 0;
  int current = gyroGet(g1);
  // Calculate w (angluar velocity in degrees per second)
  double w = (current - last_gyro) / (LOCALIZATION_UPDATE_FREQUENCY/1000.0);
  return w;
}

bool init_localization(const unsigned char gyro1, unsigned short multiplier, int start_x, int start_y, int start_theta)  {
  g1 = gyroInit(gyro1, multiplier);
  x = start_x;
  y = start_y;
  theta = start_theta;
  localization_task = taskRunLoop(update_position, LOCALIZATION_UPDATE_FREQUENCY);
  return true;
}
