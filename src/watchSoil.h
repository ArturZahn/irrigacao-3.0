#ifndef WATCHSOIL_H
#define WATCHSOIL_H

#include "Arduino.h"
#include "timeFuncs.h"

#define soilMoistureSensor 34

#define timeBetweenSoilMeasures 60000 // 1 min
// #define timeBetweenSoilMeasures 600000 // 10 min
#define numberOfSpacedSubMeasures 10
#define delayBetweenSpacedSubMeasures 3000
#define numberOfSubSubMeasures 20
#define numberOfMeasuresArray 9960
#define maxNumberOfMeasuresLimited 10

// #define fakeSoilMoistureSensor

typedef struct {
    unsigned int value;
    unsigned long time;
} measures_stc;

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
void setDebugSensor(bool);
void handleDebugSensor();

#endif