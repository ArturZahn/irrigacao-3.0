#ifndef RTC_H
#define RTC_H

#include <Arduino.h>


#include <Wire.h>
#include <DS3231.h>
#include "handlePrint.h"


void initRTC();
int readTimeFromRTC();
bool checkIfRTCIsWorking();



#endif