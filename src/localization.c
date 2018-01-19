#include "localization.h"
#include "vmath.h"
#include <inttypes.h>

static Gyro g1;
static TaskHandle localization_task;

static int last_call = 0;

matrix *state_matrix;

/**
 * @brief Structure for holding an xy position and an angle theta from the IMEs
 **/
struct encoder_odemtry {
  double x;
  double y;
  double theta;
};

/**
 * @brief Structure for holding an xy position from the accelerometer
 **/
struct accelerometer_odometry {
  double x;
  double y;
};

static double calculate_angle();
static struct accelerometer_odometry calculate_accelerometer_odemetry();

/**
 * @brief Gets the current posituion of the robot
 * @author Chris Jerrett
 * @param gyro1 The first gyro
 * @return the loacation of the robot as a struct.
 **/
struct location get_position() {}

/**
 * @brief Updates the position from the localization
 *
 * @author Chris Jerrett, Christian DeSimone
 **/
void update_position() {
  // int curr_theta = calculate_angle();

  struct accelerometer_odometry oddem = calculate_accelerometer_odemetry();
  // printf("x: %d y: %d T: %d\n", a.x, a.y, 0);

  /*int l = 1;
  int vr = get_encoder_velocity(1);
  int vl = get_encoder_velocity(2);
  int theta_dot = (vr - vl) / l;
  int curr_theta = theta + theta_dot;
  double dt = LOCALIZATION_UPDATE_FREQUENCY;
  double v_tot = (vr+vl)/2.0;
  int x_curr = x - v_tot*dt*sin(curr_theta);
  int y_curr = y + v_tot*dt*cos(curr_theta);
  x = x_curr;
  y = y_curr;*/
  last_call = millis();
}
/**
 * @brief calculats the robot's position using the accelerometer
 * @author Chris Jerrett, Christian DeSimone
 * @return the xy position of the robot
 * @see accelerometer_odometry
 **/
static struct accelerometer_odometry calculate_accelerometer_odemetry() {
  static double vel_acumm_x = 0;
  static double vel_acumm_y = 0;

  int32_t accel_x_rel = (int32_t)analogReadCalibratedHR(2);
  int32_t accel_y_rel = (int32_t)analogReadCalibratedHR(3);

  // Ignore atom format string errors
  printf("x: %+" PRId32 " y: %+" PRId32 "\n", accel_x_rel, accel_y_rel);

  double delta_time = ((millis() - last_call) / 1000.0);
  // double accel_x_abs = (accel_x_rel *  cos(theta) + accel_y_rel * sin(theta))
  // * delta_time;  double accel_y_abs = (accel_y_rel *  cos(theta) +
  // accel_x_rel
  // * sin(theta)) * delta_time;

  // vel_acumm_x += accel_x_abs;
  // vel_acumm_y += accel_y_abs;

  // double new_x = x + vel_acumm_x * delta_time;
  // double new_y = y + vel_acumm_y * delta_time;

  struct accelerometer_odometry od;
  // od.x = new_x;
  // od.y = new_y;
  return od;
}

/**
 * @brief Increases the stored angle based upon the update frequency and the current angular velocity
 * @author Chris Jerrett
 * @return returns the angle theta of the robot 
 **/
static double integrate_gyro_w(int new_w) {
  static double theta = 0;
  double delta_theta = new_w * LOCALIZATION_UPDATE_FREQUENCY;
  theta += delta_theta;
  return theta
}

/**
 * @brief calculates the angular velocity using the gyro positions
 * @author Chris Jerrett, Christian DeSimone
 * @return the angular velocity of the robot.
 **/
static double calculate_gryo_anglular_velocity() {
  static int last_gyro = 0;
  int current = gyroGet(g1);
  // Calculate w (angluar velocity in degrees per second)
  double w = (current - last_gyro) / (LOCALIZATION_UPDATE_FREQUENCY / 1000.0);
  return w;
}

/**
 * @brief calculates the current angle using the IMEs
 * @return the angle of rotation
 * @author Chris Jerrett, Christian DeSimone
 **/
int calculate_encoder_angle() {
#define WIDTH 13.5
#define CPR 392.0
#define WHEEL_RADIUS 2
  int dist_r = get_encoder_ticks(0) / CPR;
  int dist_l = get_encoder_ticks(1) / CPR;
  return ((dist_r - dist_l) / WIDTH);
}

/**
 * @brief calculates the x y posistion of the robot based upon the IMEs
 * @author Chris Jerrett, Christian DeSimone
 **/
static void calculate_encoder_odemetry() {
#define WIDTH 13.5
#define CPR 392.0
#define WHEEL_RADIUS 2

  int dist_r = get_encoder_ticks(0) / CPR;
  int dist_l = get_encoder_ticks(1) / CPR;
  printf("dist_r: %d dist_l: %d\n", dist_r, dist_l);
  int theta = (dist_l - dist_r) / WIDTH;
  printf("theta: %d\n", theta);
  int arc_length = ((M_PI * theta) * (WIDTH * WIDTH) / (8));
}

/**
 * @brief initializes the localization
 * @author Chris Jerrett
 * @return returns true when initialization is complete.
 **/
bool init_localization(const unsigned char gyro1, unsigned short multiplier,
                       int start_x, int start_y, int start_theta) {
  g1 = gyroInit(gyro1, multiplier);
  // init state matrix

  // one dimensional vector with x, y, theta, acceleration in x and y
  state_matrix = makeMatrix(1, 5);
  localization_task =
      taskRunLoop(update_position, LOCALIZATION_UPDATE_FREQUENCY * 1000);
  last_call = millis();
  return true;
}
