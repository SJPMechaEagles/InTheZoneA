/**
 * @brief The motor port definitions
 * @file motor_ports.h
 * Macros for the different motors ports.
 **/
#ifndef _MOTOT_PORTS_H_
#define _MOTOR_PORTS_H_

/**
 * @brief The max speed of a motor
 **/
#define MAX_SPEED 127

/**
 * @brief The min speed of a motor
 **/
#define MIN_SPEED -128

/**
 * @brief Front right drive motor of robot base
 * @author Christian Desimone
 * @date 9/7/2017
 **/
#define MOTOR_FRONT_RIGHT 8

/**
 * @brief Front left drive motor of robot base
 * @author Christian Desimone
 * @date 9/7/2017
 **/
#define MOTOR_FRONT_LEFT 3

/**
 * @brief Back right drive motor of robot base
 * @author Christian Desimone
 * @date 9/7/2017
 **/
#define MOTOR_BACK_RIGHT 9
/**
 * @brief Back left drive motor of robot base
 * @author Christian Desimone
 * @date 9/7/2017
 **/
#define MOTOR_BACK_LEFT 2

/**
 * @brief Port for the main lifter
 */
#define MOTOR_MAIN_LIFTER_RIGHT 6

/**
 * @brief Port for the main lifter
 */
#define MOTOR_MAIN_LIFTER_LEFT 5

/**
 * @brief The port for the roller claw
 */
#define CLAW_MOTOR 10

/**
 * @brief Port for the secondary lifter
 */
#define MOTOR_SECONDARY_LIFTER_RIGHT 7

/**
 * @brief Port for the secondary lifter
 */
#define MOTOR_SECONDARY_LIFTER_LEFT 4

/**
 * @brief Port for the main lifter
 */
#define MOBILE_INTAKE_MOTOR 1

#endif
