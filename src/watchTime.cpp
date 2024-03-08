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
                // LOGprint("time: ");
                // LOGprintln(now);
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

void pauseAutomaticProgramations()
{
    setAutomaticMode(true);
    d.areProgramationsPaused = true;
    setNeedToUpdate();

    storeEEPROMData();
}
void resumeAutomaticProgramations()
{
    setAutomaticMode(true);
    d.areProgramationsPaused = false;
    setNeedToUpdate();
    
    storeEEPROMData();
}

bool areProgramationsPaused()
{
    return d.areProgramationsPaused;
}
