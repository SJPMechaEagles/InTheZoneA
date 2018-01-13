/**
 * @file auto.h
 * @author Chris Jerrett
 * @date 9/18/2017
 * @brief Autonomous declarations and macros
 **/
#ifndef _AUTO_H_
#define _AUTO_H_

#include "claw.h"
#include "drive.h"
#include "lifter.h"
#include "sensor_ports.h"
#include "mobile_goal_intake.h"
#include "localization.h"

/**
 * @brief Front left motor integrated motor encoder
 **/
#define FRONT_LEFT_IME 0

/**
 * @brief Middle left motor integrated motor encoder
 **/
#define MID_LEFT_DRIVE 1

/**
 * @brief Middle right motor integrated motor encoder
 **/
#define MID_RIGHT_DRIVE 4

/**
 * @brief First Stop position for stationary autonomous
 **/
#define STOP_ONE 500

/**
 * @brief The height of the goal using potentiometer readings.
 **/
#define GOAL_HEIGHT 1325

/**
* @brief height at which rubber bands do a do
**/
#define DEPLOY_HEIGHT 500

#define LOWEST_HEIGHT 0

#define MOBILE_GOAL_HEIGHT 3090

#define MOBILE_GOAL_DISTANCE 4000

#define MAX_HEIGHT 3090

#define ZONE_DISTANCE 1000

#define HALF_ROTATE PI

#endif
