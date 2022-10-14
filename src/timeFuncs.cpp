#include "timeFuncs.h"

void initTime()
{
    #ifdef disableRTC
    NBprintln("RTC está desabilitado!!");
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
    // temporaryVar_time += 60;
    temporaryVar_time += 1;
    return temporaryVar_time;
        #else
    return 50400; // 14:00
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

// RTClib myRTC_2;
bool setTimeAutomatically()
{
    
    if(WiFi.status() != WL_CONNECTED) return false;

    WiFiUDP ntpUDP;
    NTPClient timeClient(ntpUDP);
    timeClient.begin();
    timeClient.setTimeOffset(-10800);

    NBprint("Getting time");
    // byte i;
    // for(i = 0; i < numberOfTriesToGetTimeFromInternet; i++) {
    //     if(timeClient.update())
    //     {
    //         break;
    //     }
    //     timeClient.forceUpdate();
    //     NBprint(".");
    // }

    // if(i >= numberOfTriesToGetTimeFromInternet)
    // {
    //     NBprint("cant get time");
    //     return false;
    // }
    // NBprintln();
    if(!timeClient.forceUpdate())
    {
        RPprintln("Não foi possível definir hora automaticamente.");
        return false;
    }
        
    RPprint("tempo definido para ");
    RPprintln(timeClient.getFormattedTime());

    DateTime nowDT = getDateTime();
    setTime(
        (byte)timeClient.getSeconds(),
        (byte)timeClient.getMinutes(),
        (byte)timeClient.getHours(),
        (byte)nowDT.day(),
        (byte)nowDT.month(),
        (int)nowDT.year()
    );

    return true;
}