#include "main.h"

void setup()
{
    #ifdef debugWifi
    initDebug();
    #endif

    initPrint();
    initializeEEPROM();
    initSections();
    initTime();
    readEEPROMData();
    initializeProgramations();
    initWifi();
}

void loop()
{
    handleWatchTime();
    handleActiveEvent();
    handleSerialControl();

    // setHandlingWifi(true);
    handleWifi();
    // setHandlingWifi(false);


    #ifdef debugWifi
    finishedMainLoop();
    #endif
}