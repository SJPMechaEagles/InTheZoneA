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
 * @brief PI
 * 3.14159268...
 */
#define M_PI 3.14159265358979323846

/**
 * @brief A struct that contains polar coordinates.
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
 * @brief A struct that contains cartesian coordinates.
 * @date 9/9/2017
 * @author Chris Jerrett
 */
struct cord {
  /** the x coordinate **/
  float x;
  /** the y coordinate **/
  float y;
};

/**
 * @brief Function to convert x and y 2 dimensional cartesian coordinated to
 * polar coordinates.
 *
 * @author Christian Desimone
 * @date 9/8/2017
 *
 * @param x float value of the x cartesian coordinate.
 * @param y float value of the y cartesian coordinate.
 * @return a struct containing the angle and magnitude.
 * @see polar_cord
 */
struct polar_cord cartesian_to_polar(float x, float y);

/**
 * @brief Function to convert x and y 2 dimensional cartesian cordinated to
 * polar coordinates.
 *
 * @author Christian Desimone
 * @date 9/8/2017
 *
 * @param cords the cartesian cords
 * @return a struct containing the angle and magnitude.
 * @see polar_cord
 * @see cord
 */
struct polar_cord cartesian_cord_to_polar(struct cord cords);

/**
 * @brief the min of two values
 * @param a the first
 * @param b the second
 * @return the smaller of a and b
 **/
int min(int a, int b);

/**
 * @brief the min of two values
 * @param a the first
 * @param b the second
 * @return the smaller of a and b
 **/
int max(int a, int b);

/**
 * @brief sine of a angle in degrees
 **/
double sind(double angle);
#endif
