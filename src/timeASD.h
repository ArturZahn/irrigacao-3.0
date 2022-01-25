#ifndef TIME_H
#define TIME_H

#include <Arduino.h>
#include "aditionalFunctions.h"
// #include "rtc.h"

#define timeEmpty 0x7FF
#define timeMax 0x59F

unsigned long getTime();
unsigned int getDayTime();




#endif