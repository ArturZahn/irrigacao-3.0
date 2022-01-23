#ifndef EVENTS_H
#define EVENTS_H

#include <Arduino.h>
#include "protectedData.h"

class Event
{
private:

public:

    programationRawData rawData;

    Event(programationRawData _rd);

    bool isEnabled();
    void setStatus(bool stt);
};

void checkEvents();

#endif