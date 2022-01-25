#include "rtc.h"

RTClib rtc;
DateTime t;

void ASDASDRTC()
{
    Serial.println("init RTC");
    if(checkIfRTCIsWorking())
    {
        Serial.println("RTC is working!");
    }
    else
    {
        Serial.println("RTC isnt working");
    }
    Serial.print("current time:");
    Serial.println(readTimeFromRTC());
}

int readTimeFromRTC()
{
    // you need to call "checkIfRTCIsWorking()" before calling "readTimeFromRTC()"
    return t.unixtime();
}

bool checkIfRTCIsWorking()
{
    t = rtc.now();
    if(t.month() == 165 || t.day() == 165 || t.hour() == 165 || t.minute() == 165 || t.second() == 85)
    {
        return false;
    }

    return true;
}