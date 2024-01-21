#ifndef RTC_H
#define RTC_H

#include <Arduino.h>


#include <Wire.h>
#include <DS3231.h>
#include "handlePrint.h"
#include "watchRainData.h"

void initRTC();
DateTime getDateTime();
int readTimeFromRTC();
bool checkIfRTCIsWorking();

bool parseTime(String, byte&, byte&, byte&, byte&, byte&, int&);
void setTime(byte, byte, byte, byte, byte, int);
bool setTime(String);



#endif