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
    initWatchSoil();

    #ifdef enableOTA
    setupOTA();
    #endif

    // pinMode(soilMoistureSensor, INPUT);
    // pinMode(panelButton, INPUT);
}

void loop()
{
    handleWatchTime();
    handleActiveEvent();
    handleSerialControl();
    handleWatchSoil();

    // setHandlingWifi(true);
    handleWifi();
    // setHandlingWifi(false);

    #ifdef enableOTA
        #if defined(ESP32_RTOS) && defined(ESP32)
        #else // If you do not use FreeRTOS, you have to regulary call the handle method.
            ArduinoOTA.handle();
        #endif
    #endif

    // NBprint("0 4096 ");
    // NBprint(millis());
    // NBprint(" ");
    // NBprintln(analogRead(soilMoistureSensor));
    // NBprintln(digitalRead(panelButton));


    #ifdef debugWifi
    finishedMainLoop();
    #endif
}