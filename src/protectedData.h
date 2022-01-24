#ifndef PROTECTEDDATA_H
#define PROTECTEDDATA_H

// #include "struct.h"
#include <Arduino.h>
#include "EEPROM.h"
#include "programationRawDataStructure.h"

#define numOfProgramations 5

struct protectedData
{
    programationRawData programationsRawData[numOfProgramations];
};

extern protectedData d;

#define EEPROM_SIZE 150

void initializeEEPROM();

template <typename T>
unsigned int writeAnything(const T& value);
template <typename T>
unsigned int readAnything(T& value);

void storeEEPROMData();
void readEEPROMData();

#endif