#ifndef CONV_H
#define CONV_H

#include "timeASD.h"
#include "events.h"

// #define timeBetweenTimeChecks 1000
#define timeBetweenTimeChecks 20

void handleWatchTime();

void pauseProgramations();
void resumeProgramations();
bool areProgramationsPaused();

#endif