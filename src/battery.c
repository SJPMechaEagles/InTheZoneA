#include "battery.h"
#include <API.h>


/**
* @brief gets the main battery voltage
* @author Chris Jerrett
**/
double main_battery_voltage() {
  return powerLevelMain() / 1000.0;
}

/**
* @brief gets the backup battery voltage
* @author Chris Jerrett
**/
double backup_battery_voltage() {
  return powerLevelBackup() / 1000.0;
}

/**
* @brief returns if the batteries are acceptable
* @see MIN_MAIN_VOLTAGE
* @see MIN_BACKUP_VOLTAGE
*
* @author Chris Jerrett
**/
bool battery_level_acceptable() {
  if(main_battery_voltage() < MIN_MAIN_VOLTAGE) return false;
  if(backup_battery_voltage() < MIN_BACKUP_VOLTAGE) return false;
  return true;
}
