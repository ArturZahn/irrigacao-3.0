#ifndef SERIAL_H
#define SERIAL_H

#include <Arduino.h>
#include "handlePrint.h"
#include "cli.h"

#define sizeOfCommand 256

void handleSerialControl();
void clearCommand();
void runSerialCommand();

#endif