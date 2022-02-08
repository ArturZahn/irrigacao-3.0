#include "main.h"

void setup()
{
    initPrint();
    initializeEEPROM();
    initSections();
    initRTC();
    readEEPROMData();
    initializeProgramations();
    initWifi();
}

void loop()
{
    handleWatchTime();
    handleActiveEvent();
    handleSerialControl();
    handleWifi();
}