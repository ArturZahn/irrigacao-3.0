#ifndef PROTECTEDDATA_H
#define PROTECTEDDATA_H

// #include "struct.h"
#include <Arduino.h>
#include "EEPROM.h"
#include "programationRawDataStructure.h"
#include "wifiDataDef.h"


#define numOfProgramations 5


struct protectedData
{
    programationRawData programationsRawData[numOfProgramations];
    bool areProgramationsPaused;
    wifiData wifi;
};

extern protectedData d;

#define EEPROM_SIZE sizeof(d)

void initializeEEPROM();

template <typename T>
unsigned int writeAnything(const T& value);
template <typename T>
unsigned int readAnything(T& value);

void storeEEPROMData();
void readEEPROMData();

#endif