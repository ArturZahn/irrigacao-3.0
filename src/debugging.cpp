#include "debugging.h"

void initDebug()
{
    pinMode(ledRedPin, OUTPUT);
    pinMode(ledYellowPin, OUTPUT);

    // blink red led
    digitalWrite(ledRedPin, HIGH);
    delay(1000);
    digitalWrite(ledRedPin, LOW);
}

// void setHandlingWifi(bool s)
// {
//     digitalWrite(ledRedPin, s);
// }

unsigned int ledToggleTime = ledToggleTimeDisconnected;
unsigned long lastLedToggleTime = 0;
bool lastConnected = false;

bool ledStatus = false;
void finishedMainLoop()
{
    bool connected = isConnectedToWifi();
    if(connected != lastConnected)
    {
        if(connected) ledToggleTime = ledToggleTimeConnected;
        else ledToggleTime = ledToggleTimeDisconnected;

        lastConnected = connected;
    }

    if(millis() - lastLedToggleTime > ledToggleTime)
    {
        ledStatus = !ledStatus;
        lastLedToggleTime = millis();
        
        digitalWrite(ledYellowPin, ledStatus);
    }
}