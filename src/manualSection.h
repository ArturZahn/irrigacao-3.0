#ifndef MANUALSECTION_H
#define MANUALSECTION_H

#include <Arduino.h>
#include "sections.h"
#include "protectedData.h"
#include "automaticMode.h"

bool setDefaultManualSection(byte sectionNum);
byte getDefaultManualSection();

bool activateManualSection(byte sectionNum);
void deactivateManualSection();
byte getActiveManualSection();

#endif