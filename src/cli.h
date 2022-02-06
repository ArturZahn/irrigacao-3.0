#ifndef CLI_H
#define CLI_H

#include <Arduino.h>
#include "aditionalFunctions.h"
#include "alterProgramation.h"
#include "watchTime.h"
#include "wifiHandler.h"

#define CLI_SOURCE_OTHER 255
#define CLI_SOURCE_SERIAL 1
#define CLI_SOURCE_WIFI 2

void cliRunCommand(String cmd, byte cmdSource);

#endif