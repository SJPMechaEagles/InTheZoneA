/**
 * @file battery.h
 * @author Chris Jerrett
 * @date 9/18/2017
 * @brief Battery management related functions
 **/
#ifndef _BATTERY_H_
#define _BATTERY_H_

#include <API.h>

/**
 * @brief The minimum acceptable main battery voltage beofre a match.
 **/
#define MIN_MAIN_VOLTAGE 7.8

/**
 * @brief The minimum acceptable backup battery voltage beofre a match.
 **/
#define MIN_BACKUP_VOLTAGE 7.8

/**
 * @brief gets the main battery voltage
 * @author Chris Jerrett
 **/
double main_battery_voltage();

/**
 * @brief gets the backup battery voltage
 * @author Chris Jerrett
 **/
double backup_battery_voltage();

/**
 * @brief returns if the batteries are acceptable
 * @see MIN_MAIN_VOLTAGE
 * @see MIN_BACKUP_VOLTAGE
 *
 * @author Chris Jerrett
 **/
bool battery_level_acceptable();

#endif
