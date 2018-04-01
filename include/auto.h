/**
 * @file auto.h
 * @authors Chris Jerrett, Christian Desimone
 * @date 9/18/2017
 * @brief Autonomous declarations and macros
 **/
#ifndef _AUTO_H_
#define _AUTO_H_

#include "claw.h"
#include "drive.h"
#include "lifter.h"
#include "localization.h"
#include "mobile_goal_intake.h"
#include "sensors.h"

enum FIELD_COLOR{ COLOR_NOT_SET = -1, RED = 0, BLUE = 1 };
enum FIELD_SIDE { SIDE_NOT_SET = -1, DRIVER_SIDE = 0, NOT_DRIVER_SIDE = 1 };


#define ROTATION_SPEED 60

/**
 * @brief Middle left motor integrated motor encoder
 **/
#define FRONT_RIGHT_IME 3

/**
 * @brief Middle right motor integrated motor encoder
 **/
#define FRONT_LEFT_IME 2

/**
 * @brief  right motor integrated motor encoder
 **/
#define BACK_LEFT_IME 1

/**
 * @brief Middle right motor integrated motor encoder
 **/
#define BACK_RIGHT_IME 0

/**
 * @brief First Stop position for stationary autonomous
 **/
#define STOP_ONE 500

/**
 * @brief The height of the goal using potentiometer readings.
 **/
#define GOAL_HEIGHT 1325

/**
 * @brief height at which rubber bands release claw
 **/
#define DEPLOY_HEIGHT 3500

/**
 * @brief the lowest height of the secondary lifter
 **/
#define LOWEST_HEIGHT 0

/**
 * @brief the height of the second lifter for deploying the mobile goal lifter,
 *posibly fixed in hardware
 **/
#define MOBILE_GOAL_HEIGHT 1800

/**
 * @brief The distance to drive, in encoder ticks, to reach the mobile goal from
 *the starting zone
 **/
#define MOBILE_GOAL_DISTANCE 2000

#define STATIONARY_GOAL_DISTANCE 1000

void autonomous();

/**
 * @brief the maximum height of the secondary lifter
 **/
#define MAX_HEIGHT 3570
/**
 * @brief the distance to be traveled by the robot after obtaining the mobile
 *goal
 **/
#define ZONE_DISTANCE 1000
/**
 * @brief 180 degrees in radians
 **/
#define HALF_ROTATE M_PI

#endif
