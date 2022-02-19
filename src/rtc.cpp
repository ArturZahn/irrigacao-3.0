#include "rtc.h"

RTClib myRTC;

DateTime t;

void initRTC()
{
    Wire.begin();


    if(checkIfRTCIsWorking())
    {
        NBprintln("RTC is working!");
    }
    else
    {
        NBprintln("RTC isnt working");
    }
}

int readTimeFromRTC()
{
    // you need to call "checkIfRTCIsWorking()" before calling "readTimeFromRTC()"
    return t.unixtime();
}

bool checkIfRTCIsWorking()
{
    t = myRTC.now();
    if(t.month() == 165 || t.day() == 165 || t.hour() == 165 || t.minute() == 165 || t.second() == 85)
    {
        return false;
    }

    return true;
}