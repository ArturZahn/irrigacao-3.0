#ifndef ADITIONALFUNCTIONS_H
#define ADITIONALFUNCTIONS_H

#include <Arduino.h>
#include "handlePrint.h"
// #include "Esp.h"

void restartSystem();
void splitCmdArgs(String cmdArgs, String *cmd, String *args);

#endif