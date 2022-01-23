#include "events.h"

// Date constructor
Event::Event(programationRawData _rd)
{
    rawData = _rd;
}

// Date member function
bool Event::isEnabled()
{
    // just get the 5th most significant bit of rawData.statusAndActivationTime
    return bitRead(rawData.statusAndActivationTime, statusBit);
}

void Event::setStatus(bool stt)
{
    bitWrite(rawData.statusAndActivationTime, statusBit, stt);
}



void checkEvents()
{
    Serial.println("let's check the events");
    Serial.println(d.programationsRawData->statusAndActivationTime);
    // Serial.println(global);
}