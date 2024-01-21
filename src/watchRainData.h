#ifndef ASD_H
#define ASD_H

#include <Arduino.h>
#include <vector>
#include <WiFiClient.h>
#include "timeFuncs.h"

// #define timeBetweenSucessfulRainDataRequest 1800000
// #define timeBetweenRainDataRequestAttemps    300000
#define timeBetweenSucessfulRainDataRequest 10000
#define timeBetweenRainDataRequestAttemps    1000

#define maxRainDataAge 24.0
#define milimetersOfRainToConsiderMoist 10.0

typedef struct {
    unsigned long unixtime;
    double rain;
} rainData_t;

void handleWatchRainData();
bool updateRainData();
bool debugRainData();
bool updateRainData(bool);
bool filterData();
bool readResponseUntilAndSaveToString(String, String*);
bool readResponseUntil(String);
void clearRainData();
void printRainData();
void filterOutOldData();
unsigned int sumRainFromData();
bool isAlreadyMoist();

#endif