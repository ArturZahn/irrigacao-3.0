#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include "handlePrint.h"
#include "watchTime.h"
#include "programations.h"
#include "serialControl.h"
#include "timeFuncs.h"
#include "rtc.h"
#include "wifiHandler.h"
#include "automaticMode.h"

#define debugWifi
#ifdef debugWifi
    #define ledRedPin 10
    #define ledYellowPin 11

    #define ledToggleTime 1000
#endif

void setup();
void loop();

#endif