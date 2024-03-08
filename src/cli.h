#ifndef CLI_H
#define CLI_H

#include <Arduino.h>
#include "aditionalFunctions.h"
#include "alterProgramation.h"
#include "watchTime.h"
#include "wifiHandler.h"
#include "manualSection.h"
#include "timeFuncs.h"
#include "wifiHandler.h"
// #include "watchSoil.h"
#include "watchRainData.h"

void cliRunCommand(String cmd);

void handleShowInformation();

#endif