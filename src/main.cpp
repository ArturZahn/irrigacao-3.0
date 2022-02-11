#include "main.h"

void setup()
{
    #ifdef debugWifi
    pinMode(ledRedPin, OUTPUT);
    pinMode(ledYellowPin, OUTPUT);
    #endif

    initPrint();
    initializeEEPROM();
    initSections();
    initRTC();
    readEEPROMData();
    initializeProgramations();
    initWifi();
}


#ifdef debugWifi
unsigned long lastLedToggleTime = 0;
#endif
void loop()
{
    handleWatchTime();
    handleActiveEvent();
    handleSerialControl();

    #ifdef debugWifi
    digitalWrite(ledRedPin, HIGH);
    #endif
    handleWifi();
    #ifdef debugWifi
    digitalWrite(ledRedPin, LOW);

    if(millis() - lastLedToggleTime > ledToggleTime)
    {
        lastLedToggleTime = millis();
        digitalWrite(ledYellowPin, !digitalRead(ledYellowPin));
    }
    #endif
}