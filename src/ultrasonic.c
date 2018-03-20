#include "ultrasonic.h"
#include <API.h>
Ultrasonic u1;
Ultrasonic u2;

void init_dual_ultrasonic() { 
	u1 = ultrasonicInit(1, 2); 
	u2 = ultrasonicInit(3, 4);
}

bool is_cone_detected() { return ultrasonicGet(u1) == ULTRA_BAD_RESPONSE; }

void deinit_dual_ultrasonic() { ultrasonicShutdown(u1); }
