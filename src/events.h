#ifndef EVENTS_H
#define EVENTS_H

#include <Arduino.h>
#include "programations.h"
#include "automaticMode.h"

void checkEvents(int *now);
byte findProgramationToStartNow(int *now);

#define stageDurationMultiplier 60000 //in minutes
// #define stageDurationMultiplier 1000 //in seconds

void handleActiveEvent();
bool startEvent(byte programationToStart);
void stopEvent();
byte getActiveProgramation();

#endif