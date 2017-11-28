/**
* @file auto.h
* @author Chris Jerrett
* @date 9/18/2017
* @brief Autonomous declarations and macros
**/
#ifndef _AUTO_H_
#define _AUTO_H_

#include "drive.h"
#include "sensor_ports.h"
#include "lifter.h"
#include "claw.h"

/**
* Front left motor integrated motor encoder
**/
#define FRONT_LEFT_IME 0

/**
* Middle left motor integrated motor encoder
**/
#define MID_LEFT_DRIVE 1

/**
* Middle right motor integrated motor encoder
**/
#define MID_RIGHT_DRIVE 4

/**
* First Stop position for stationary autonomous
**/
#define STOP_ONE 500

/**
* The height of the goal using potentiometer readings.
**/
#define GOAL_HEIGHT 1325


#endif
