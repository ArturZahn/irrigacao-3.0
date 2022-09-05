#ifndef SECTIONS_H
#define SECTIONS_H

#include <Arduino.h>
#include "protectedData.h"

// uncomment the following line to test if it can turn all sections at the same time without restarting
// #define enableAllSectionsWhenOneIsActivated
// remove all comments with this ↓↓
//#$# 

#define numOfSections 4
#define sectionEmpty 255

#define commonPin 32
#define pumpPin 33
#define section0 25
#define section1 26
#define section2 27
#define section3 14

void initSections();
byte getSectionPin(byte sectionNum);
void digiWrite(byte pin, bool stt);
void activateSection(byte sectionNum);
void deactivateAllSections();


#endif