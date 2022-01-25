#include "watchTime.h"

unsigned long lastTimeCheck = 0;
int lastDayTime = 0;

void handleWatchTime()
{
    if(millis() - lastTimeCheck > timeBetweenTimeChecks)
    {
        lastTimeCheck = millis();

        int now = getDayTime();
        if(now != lastDayTime)
        {
            // new minute!
            // if(now%50==0)
            // {
                Serial.print("time: ");
                Serial.println(now);
            // }

            // continue only if programations are not paused
            if(!areProgramationsPaused())
            {
                checkEvents(&now);
            }

            lastDayTime = now;
        }
    }
}

void pauseProgramations()
{
    d.areProgramationsPaused = true;
    stopEvent();

    storeEEPROMData();

    Serial.println("programations paused");
}
void resumeProgramations()
{
    d.areProgramationsPaused = false;
    
    storeEEPROMData();

    Serial.println("programations resumed");
}

bool areProgramationsPaused()
{
    return d.areProgramationsPaused;
}
