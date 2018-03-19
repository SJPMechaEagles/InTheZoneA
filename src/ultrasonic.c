#include "ultrasonic.h"
#include <API.h>
Ultrasonic u;

void init_dual_ultrasonic() { u = ultrasonicInit(ECHO, PING); }

bool is_cone_detected() { return true ? ultrasonicGet(u) == -1 : false; }

void deinit_dual_ultrasonic() { ultrasonicShutdown(u); }
