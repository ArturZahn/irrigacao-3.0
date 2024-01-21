#ifndef RTC_H
#define RTC_H

#include <Arduino.h>


#include <Wire.h>
#include <DS3231.h>
#include "handlePrint.h"


void initRTC();
DateTime getDateTime();
int readTimeFromRTC();
bool checkIfRTCIsWorking();

void setTime(byte second, byte minute, byte hour, byte date, byte month, int year);
bool setTime(String datetime);



#endif