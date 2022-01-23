#include "watchTime.h"

unsigned long lastTimeCheck = 0;
int lastDayTime = 0;

void handdleWatchTime()
{
    if(millis() - lastTimeCheck > timeBetweenTimeChecks)
    {
        Serial.print("checking...");
        lastTimeCheck = millis();

        int now = getDayTime();
        Serial.print(now);
        Serial.print(" ");
        if(now != lastDayTime)
        {
            // new minute!
            lastDayTime = now;
        }
        
        Serial.println("");
    }

}