#ifndef WATCHSOIL_H
#define WATCHSOIL_H

#include "Arduino.h"
#include "timeFuncs.h"

#define soilMoistureSensor 34

// #define timeBetweenSoilMeasures 1800000 // 30 min
#define timeBetweenSoilMeasures 15000
#define numberOfSpacedSubMeasures 3
#define delayBetweenSpacedSubMeasures 3000
#define numberOfSubSubMeasures 10
// #define numberOfMeasuresArray 10000
#define numberOfMeasuresArray 10000
#define maxNumberOfMeasuresLimited 10

// #define fakeSoilMoistureSensor

typedef struct {
    unsigned int value;
    unsigned long time;
} measures_stc;

// unsigned int nOfStoredMeasures;
// measures_stc measures[numberOfMeasuresArray];

void initWatchSoil();
void handleWatchSoil();
void handleSoilMeasuring();
void startMeasuringSoil();
unsigned int makeSubMeasure();
void handleNewMeasure(unsigned int);
unsigned int showSoilMeasuringsLimited(unsigned int);
unsigned int showSoilMeasurings(unsigned int);
void showSoilMeasurings();
void clearSoilMeasurings(unsigned int);
void clearSoilMeasurings();
void showAndClearSoilMeasurings();

#endif