/**
* @file ports.h
* @author Chris Jerrett
* @date 9/9/2017
* @brief contains port macros for sensors
**/

#ifndef _PORTS_H_
#define  _PORTS_H_

/**
* @brief Number of integrated motor encoders
* Used when checking to see if all imes are plugged in
* @see init_encoders
* @author Christian Desimone
* @date 9/7/2017
**/
#define IME_FRONT_RIGHT 0

/**
* @brief Front right drive motor of robot base
* @author Christian Desimone
* @date 9/7/2017
**/
#define MOTOR_FRONT_RIGHT 0

/**
* @brief Front left drive motor of robot base
* @author Christian Desimone
* @date 9/7/2017
**/
#define MOTOR_FRONT_LEFT 1

/**
* @brief Middle right drive motor of robot base
* @author Christian Desimone
* @date 9/7/2017
**/
#define MOTOR_MIDDLE_RIGHT 2

/**
* @brief Middle left drive motor of robot base
* @date 9/7/2017
* @author Christian Desimone
**/
#define MOTOR_MIDDLE_LEFT 3
/**
* @brief Back right drive motor of robot base
* @author Christian Desimone
* @date 9/7/2017
**/
#define MOTOR_BACK_RIGHT 4
/**
* @brief Back left drive motor of robot base
* @author Christian Desimone
* @date 9/7/2017
**/
#define MOTOR_BACK_LEFT 5

#endif
