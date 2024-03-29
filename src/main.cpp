#include "main.h"

void setup()
{
    // initialize remote serial first to log all serial data since the begining
    initializeRemoteSerial();

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
    // initWatchSoil();

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
    // handleWatchSoil();

    // setHandlingWifi(true);
    handleWifi();
    // setHandlingWifi(false);

    handlePeriodicTimeAjust();
    handleWatchRainData();

    #ifdef enableOTA
        #if defined(ESP32_RTOS) && defined(ESP32)
        #else // If you do not use FreeRTOS, you have to regulary call the handle method.
            ArduinoOTA.handle();
        #endif
    #endif

    // LOGprint("0 4096 ");
    // LOGprint(millis());
    // LOGprint(" ");
    // LOGprintln(analogRead(soilMoistureSensor));
    // LOGprintln(digitalRead(panelButton));


    #ifdef debugWifi
    finishedMainLoop();
    #endif
}