#ifndef DEBUGGING_H
#define DEBUGGING_H

#include <Arduino.h>
#include "wifiHandler.h"

#define debugWifi
#ifdef debugWifi
    #define ledRedPin 12
    #define ledYellowPin 13

    #define ledToggleTimeConnected 2000
    #define ledToggleTimeDisconnected 500
#endif

#endif

void initDebug();
// void setHandlingWifi(bool s);
void finishedMainLoop();