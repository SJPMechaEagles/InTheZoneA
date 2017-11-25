#include "battery.h"
#include <API.h>

double main_battery_voltage() {
  return powerLevelMain() / 1000.0;
}

double backup_battery_voltage() {
  return powerLevelBackup() / 1000.0;
}

bool battery_level_acceptable() {
  if(main_battery_voltage() < MIN_MAIN_VOLTAGE) return false;
  if(backup_battery_voltage() < MIN_BACKUP_VOLTAGE) return false;
  return true;
}
