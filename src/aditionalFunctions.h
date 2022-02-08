#ifndef ADITIONALFUNCTIONS_H
#define ADITIONALFUNCTIONS_H

#include <Arduino.h>
#include "handlePrint.h"

void restartSystem();

void splitCmdArgs(String cmdArgs, String *cmd, String *args);

String urlDecode(String str);

bool isNumber(const String& str);

#endif