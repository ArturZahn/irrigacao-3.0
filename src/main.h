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
#include "debugging.h"

#define enableOTA
#ifdef enableOTA
#include "ota.h"
#endif

// #define soilMoistureSensor 34
// #define panelButton 35

void setup();
void loop();

#endif