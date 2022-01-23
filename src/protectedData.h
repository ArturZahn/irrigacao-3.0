#ifndef PROTECTEDDATA_H
#define PROTECTEDDATA_H

// #include "struct.h"
#include <Arduino.h>
#include "programationRawDataStructure.h"

#define numOfProgramations 5

struct protectedData
{
    programationRawData programationsRawData[numOfProgramations];
};

extern protectedData d;

// void teste();

#endif