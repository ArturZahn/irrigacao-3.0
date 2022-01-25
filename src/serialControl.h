#ifndef SERIAL_H
#define SERIAL_H

#include <Arduino.h>
#include "alterProgramation.h"
#include "watchTime.h"

#define sizeOfCommand 256

void handleSerialControl();
void clearCommand();
void runCommand();

#endif