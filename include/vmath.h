/**
* @file vmath.h
* @author Christian Desimone
* @author Chris Jerrett
* @date 9/9/2017
* @brief Vex Specific Math Functions, includes: Cartesian to polar cordinates.
**/

#ifndef _VMATH_H_
#define _VMATH_H_

#include <math.h>

/**
* @brief A struct that contains polar cordinates.
* @date 9/9/2017
* @author Chris Jerrett
*/
struct polar_cord {
  /** the angle of the vector **/
  float angle;
  /** the magnitude of the vector **/
  float magnitue;
};

/**
* @brief A struct that contains cartesian cordinates.
* @date 9/9/2017
* @author Chris Jerrett
*/
struct cord {
  /** the x cordinate **/
  float x;
  /** the y cordinate **/
  float y;
};

struct polar_cord cartesian_to_polar(float x, float y);
struct polar_cord cartesian_cord_to_polar(struct cord cords);

/**
* @brief Function to convert x and y 2 dimensional cartesian cordinated to polar pordinates.
*
* @author Christian Desimone
* @date 9/8/2017
*
* @param x float value of the x cartesian cordinate.
* @param y float value of the y cartesian cordinate.
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
* @brief Function to convert x and y 2 dimensional cartesian cordinated to polar pordinates.
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

#endif
