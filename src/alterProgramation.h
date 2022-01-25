#ifndef ALTERPROGRAMATION_H
#define ALTERPROGRAMATION_H

#include <Arduino.h>
#include "protectedData.h"
#include "programations.h"
#include "sections.h"
#include "timeASD.h"

void showProgramations();
void alterProgramation(String &args);
byte ajustMax(int number, byte max);

#endif