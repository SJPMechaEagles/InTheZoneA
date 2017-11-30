#include "vmath.h"

/**
* @brief Function to convert x and y 2 dimensional cartesian coordinated to polar coordinates.
*
* @author Christian Desimone
* @date 9/8/2017
*
* @param x float value of the x cartesian coordinate.
* @param y float value of the y cartesian coordinate.
* @return a struct containing the angle and magnitude.
* @see polar_cord
*/
struct polar_cord cartesian_to_polar(float x, float y) {
  float degree = 0;
  double magnitude = sqrt((fabs(x) * fabs(x)) + (fabs(y) * fabs(y)));

  if(x < 0){
    degree += 180.0;
  }
  else if(x > 0 && y < 0){
    degree += 360.0;
  }

  if(x != 0 && y != 0){
    degree += atan((float)y / (float)x);
  }
  else if(x == 0 && y > 0){
    degree = 90.0;
  }
  else if(y == 0 && x < 0){
    degree = 180.0;
  }
  else if(x == 0 && y < 0){
    degree = 270.0;
  }

  struct polar_cord p;
  p.angle = degree;
  p.magnitue = magnitude;
  return p;
}

/**
* @brief Function to convert x and y 2 dimensional cartesian cordinated to polar coordinates.
*
* @author Christian Desimone
* @date 9/8/2017
*
* @param cords the cartesian cords
* @return a struct containing the angle and magnitude.
* @see polar_cord
* @see cord
*/
struct polar_cord cartesian_cord_to_polar(struct cord cords) {
  return cartesian_to_polar(cords.x, cords.y);
}

/**
* @brief sine of a angle in degrees
**/
double sind(double angle) {
    double angleradians = angle * M_PI / 180.0f;
    return sin(angleradians);
}

/**
* @brief the min of two values
* @param a the first
* @param b the second
* @return the smaller of a and b
**/
int min(int a, int b) {
  if(a < b) return a;
  return b;
}

/**
* @brief the min of two values
* @param a the first
* @param b the second
* @return the smaller of a and b
**/
int max(int a, int b) {
  if(a > b) return a;
  return b;
}
