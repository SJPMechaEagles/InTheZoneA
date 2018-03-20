#ifndef _ULTRASONIC_H_
#define _ULTRASONIC_H_


#include <API.h>

#define PING 1
#define ECHO 2

#define PING_TWO 3
#define ECHO_TWO 4

void init_dual_ultrasonic();
bool is_cone_detected();

#define THRESHOLD 0

#endif
