#include "timeASD.h"

unsigned long temporaryVar_time = 1577836800;
unsigned long getTime()
{
    // checkIfRTCIsWorking();
    // readTimeFromRTC();
    temporaryVar_time += 60;
    return temporaryVar_time;
}

unsigned int getDayTime()
{
    return (getTime()%86400)/60;
}


////////////////////////////////////////////////

// void initRTC()
// {
    // Serial.println("starting RTC...");
//   Wire.begin();  // inicia RTC

//   DateTime t = rtc.now();

//   Serial.print(t.hour());
//   Serial.print(":");
//   Serial.print(t.minute());
//   Serial.print(":");
//   Serial.print(t.second());
//   Serial.print(" ");
//   Serial.print(t.day());
//   Serial.print(":");
//   Serial.print(t.month());
//   Serial.print(":");
//   Serial.print(t.year());
// }