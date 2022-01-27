#ifndef ALTERPROGRAMATION_H
#define ALTERPROGRAMATION_H

#include <Arduino.h>
#include "protectedData.h"
#include "programations.h"
#include "sections.h"
#include "timeFuncs.h"

void showProgramations();
void alterProgramation(String &args);
byte ajustMax(int number, byte max);
unsigned int ajustMaxuint(int number, unsigned int max);

#endif