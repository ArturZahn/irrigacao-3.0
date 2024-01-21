#include "rtc.h"

RTClib myRTC;
DS3231 myRTC_DS_tmp;
DateTime t;

void initRTC()
{
    Wire.begin();


    if(checkIfRTCIsWorking())
    {
        LOGprintln("RTC is working!");
    }
    else
    {
        LOGprintln("RTC isnt working");
    }
}

DateTime getDateTime()
{
    return t;
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

void setTime(byte second, byte minute, byte hour, byte date, byte month, int year)
{
    myRTC_DS_tmp.setSecond(second);
    myRTC_DS_tmp.setMinute(minute);
    myRTC_DS_tmp.setHour(hour);
    myRTC_DS_tmp.setDate(date);
    myRTC_DS_tmp.setMonth(month);
    myRTC_DS_tmp.setYear(year - 2000);
}

bool parseTime(String datetime, byte& second, byte& minute, byte& hour, byte& day, byte& month, int& year)
{
    // datetime formats:
    // hh:mm:ss dd/mm/yyyy 
    // hh:mm:ss yyyy-mm-dd
    char carac = ':';

    byte tp = datetime.indexOf(carac);
    if(tp == -1) return false;
    hour = datetime.substring(0, tp).toInt();
    datetime = datetime.substring(tp+1);
    
    tp = datetime.indexOf(carac);
    if(tp == -1) return false;
    minute = datetime.substring(0, tp).toInt();
    datetime = datetime.substring(tp+1);
    
    tp = datetime.indexOf(' ');
    if(tp == -1) return false;
    second = datetime.substring(0, tp).toInt();
    datetime = datetime.substring(tp+1);

    carac = '/';
    bool portugueseFormat = true;
    if(datetime.indexOf(carac) == -1)
    {
        carac = '-';
        portugueseFormat = false;
    }

    tp = datetime.indexOf(carac);
    if(tp == -1) return false;
    if(portugueseFormat) day = datetime.substring(0, tp).toInt();
    else year = datetime.substring(0, tp).toInt();
    datetime = datetime.substring(tp+1);

    tp = datetime.indexOf(carac);
    if(tp == -1) return false;
    month = datetime.substring(0, tp).toInt();
    datetime = datetime.substring(tp+1);

    if(portugueseFormat) year = datetime.toInt();
    else day = datetime.toInt();

    return true;
}

bool setTime(String dateTimeStr)
{
    byte second, minute, hour, day, month; int year;
    parseTime(dateTimeStr, second, minute, hour, day, month, year);

    setTime(second, minute, hour, day, month, year);

    return true;
}