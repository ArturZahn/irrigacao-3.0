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
    //         NBprintln("failed reading RTC time");
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
    // NBprintln("starting RTC...");
//   Wire.begin();  // inicia RTC

//   DateTime t = rtc.now();

//   NBprint(t.hour());
//   NBprint(":");
//   NBprint(t.minute());
//   NBprint(":");
//   NBprint(t.second());
//   NBprint(" ");
//   NBprint(t.day());
//   NBprint(":");
//   NBprint(t.month());
//   NBprint(":");
//   NBprint(t.year());
// }