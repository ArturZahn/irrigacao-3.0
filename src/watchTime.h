#ifndef CONV_H
#define CONV_H

#include "timeFuncs.h"
#include "events.h"
#include "automaticMode.h"
#include "wifiControlPanel.h"

// #define timeBetweenTimeChecks 1000
#define timeBetweenTimeChecks 20

void handleWatchTime();

void pauseAutomaticProgramations();
void resumeAutomaticProgramations();
bool areProgramationsPaused();

#endif