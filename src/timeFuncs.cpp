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
}

String getStrDateTime(unsigned long unixTime)
{
    DateTime t(unixTime);
    String str = "";
    if(t.hour() < 10) str += "0";
    str += ((String)t.hour())+":";

    if(t.minute() < 10) str += "0";
    str += ((String)t.minute())+":";

    if(t.second() < 10) str += "0";
    str += ((String)t.second())+" ";

    if(t.day() < 10) str += "0";
    str += ((String)t.day())+"/";

    if(t.month() < 10) str += "0";
    str += ((String)t.month())+"/";

    str += ((String)t.year());

    return str;
}

bool setTimeAutomatically()
{
    if(WiFi.status() != WL_CONNECTED) return false;
    // if(!isConnectedToWifi()) return false;

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