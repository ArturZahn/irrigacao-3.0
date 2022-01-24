#include "events.h"

void checkEvents()
{
    Serial.println("checking events...");

    byte newProgramation = findProgramationToStartNow();
    if(newProgramation != programationEmpty)
    {
        // startEvent(newProgramation);
    }
}

byte findProgramationToStartNow()
{
    for(int i = 0; i < numOfProgramations; i++)
    {
        if(programations[i].isNow())
        {
            return i;
        }
    }

    return programationEmpty;
}