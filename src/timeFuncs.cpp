#include "timeFuncs.h"

// unsigned long temporaryVar_time = 1577836800;
unsigned long getTime()
{
    // temporaryVar_time += 60;
    // return temporaryVar_time;

    // byte i = 0;
    // while(!checkIfRTCIsWorking())
    // {
    //     i++;
    //     initRTC();

    //     if(i >= numbOfRetriesConnecRTC) 
    //     {
    //         Serial.println("failed reading RTC time");
    //         restartSystem();
    //     }
    // }

    // return readTimeFromRTC();

    return 50400; // 14:00:00
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