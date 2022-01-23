#include <Arduino.h>
#include "watchTime.h"

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    handdleWatchTime();

}