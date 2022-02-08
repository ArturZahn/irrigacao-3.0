#ifndef ALTERPROGRAMATION_H
#define ALTERPROGRAMATION_H

#include <Arduino.h>
#include "protectedData.h"
#include "programations.h"
#include "sections.h"
#include "timeFuncs.h"
#include "wifiControlPanel.h"

void showProgramations();
void handleAlterProgramation(String &args);
byte ajustMax(int number, byte max);
unsigned int ajustMaxuint(int number, unsigned int max);

#endif