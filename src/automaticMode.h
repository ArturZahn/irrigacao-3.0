#ifndef AUTOMATICMODE_H
#define AUTOMATICMODE_H

#include "manualSection.h"
#include "watchTime.h"

bool isAutomaticModeEnabled();
void setAutomaticMode(bool mode);
void handleEnterAutomaticMode();
void handleLeaveAutomaticMode();

#endif