#include "timeFuncs.h"

void initTime()
{
    #ifdef disableRTC
    LOGprintln("RTC está desabilitado!!");
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
            LOGprintln("failed reading RTC time");
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

String getStrDateTime()
{
    return getStrDateTime(getTime());
    
    // LOGprintln("FFFF1");
    // String r = getStrDateTime(1000);
    // LOGprintln("FFFF2");
    // return r;
}

String getStrDateTime(unsigned long unixTime)
{
    // LOGprintln("ASDF1");
    DateTime t(unixTime);
    // LOGprintln("ASDF2");
    String str = "";
    // LOGprintln("ASDF3");
    if(t.hour() < 10) str += "0";
    str += t.hour()+":";

    // LOGprintln("ASDF4");
    if(t.minute() < 10) str += "0";
    str += t.minute()+":";

    // LOGprintln("ASDF5");
    if(t.second() < 10) str += "0";
    str += t.second()+" ";

    // LOGprintln("ASDF6");
    if(t.day() < 10) str += "0";
    str += t.day()+"/";

    // LOGprintln("ASDF7");
    if(t.month() < 10) str += "0";
    str += t.month()+"/";

    // LOGprintln("ASDF8");
    str += t.year();

    // LOGprintln("ASDF9");
    return str;
}

bool setTimeAutomatically()
{
    return false; // @#@
    if(!isConnectedToWifi()) return false;

    WiFiUDP ntpUDP;
    NTPClient timeClient(ntpUDP);
    timeClient.begin();
    timeClient.setTimeOffset(-10800);

    if(!timeClient.forceUpdate())
    {
        RPprintln("Could not set time automatically.");
        return false;
    }

    DateTime newDT = timeClient.getEpochTime();
        
    RPprint("Time set to ");
    RPprintln(getStrDateTime(newDT.unixtime()));

    setTime(
        (byte) newDT.second(),
        (byte) newDT.minute(),
        (byte) newDT.hour(),
        (byte) newDT.day(),
        (byte) newDT.month(),
        (int)  newDT.year()
    );

    return true;
}

unsigned long lastSucessfulTimeAjust = -timeBetweenSucessfulTimeAjust;
unsigned long lastTimeAjustAttempt = -timeBetweenTimeAjustAttemps;
void handlePeriodicTimeAjust()
{
    unsigned long temp = millis() - lastSucessfulTimeAjust;
    if(!(temp > timeBetweenSucessfulTimeAjust))
        return;

    temp = millis() - lastTimeAjustAttempt;
    if(!(temp > timeBetweenTimeAjustAttemps))
        return;

    lastTimeAjustAttempt = millis();    
    
    if(setTimeAutomatically())
    {
        lastSucessfulTimeAjust = lastTimeAjustAttempt;
    }
}