#include "timeFuncs.h"

void initTime()
{
    #ifdef disableRTC
    NBprint("RTC está desabilitado!!");
    #else
    initRTC();
    #endif
}

#ifdef disableRTC
    #ifdef jumpOneMinuteEveryGetTimeRequest
unsigned long temporaryVar_time = 1577836800;
    #endif
#endif
unsigned long getTime()
{
    #ifdef disableRTC
        #ifdef jumpOneMinuteEveryGetTimeRequest
    temporaryVar_time += 60;
    return temporaryVar_time;
        #else
    return 50400; // 14:00:00
        #endif
    #else

    byte i = 0;
    while(!checkIfRTCIsWorking())
    {
        i++;
        initRTC();

        if(i >= numbOfRetriesConnecRTC) 
        {
            NBprintln("failed reading RTC time");
            restartSystem();
        }
    }

    return readTimeFromRTC();
    #endif

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