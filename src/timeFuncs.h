#ifndef TIMEFUNCS_H
#define TIMEFUNCS_H

#include <Arduino.h>
#include "aditionalFunctions.h"
#include "rtc.h"

// #define disableRTC
// #define jumpOneMinuteEveryGetTimeRequest

#define timeEmpty 0x7FF
#define timeMax 0x59F

#define numbOfRetriesConnecRTC 5

void initTime();
unsigned long getTime();
unsigned int getDayTime();

#endif