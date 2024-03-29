#ifndef ASD_H
#define ASD_H

#include <Arduino.h>
#include <vector>
#include <WiFiClient.h>
#include "timeFuncs.h"
#include "wifiHandler.h"

#define timeBetweenSucessfulRainDataRequest 1800000
#define timeBetweenRainDataRequestAttempts   300000
#define timeBetweenRainDataSubAttemps 5000
#define rainDataNumOfSubAttemps 5

#define maxRainDataAge 24.0
#define milimetersOfRainToConsiderMoist 10.0

typedef struct {
    unsigned long unixtime;
    double rain;
} rainData_t;

void handleWatchRainData();
bool updateRainData();
bool filterData();
bool readResponseUntilAndSaveToString(String, String*);
bool readResponseUntil(String);
void clearRainData();
void printRainData();
void filterOutOldData();
unsigned int sumRainFromData();
bool isAlreadyMoist();

#endif