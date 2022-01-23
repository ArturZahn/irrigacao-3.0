#include <Arduino.h>
#include "watchTime.h"
#include "protectedData.h"

void setup()
{
    Serial.begin(115200);
    Serial.println(d.programationsRawData->statusAndActivationTime);

    d.programationsRawData->statusAndActivationTime = 15;
}

void loop()
{
    handdleWatchTime();
    
    d.programationsRawData->statusAndActivationTime += 1;
}