#ifndef SECTIONS_H
#define SECTIONS_H

#include <Arduino.h>

#define numOfSections 4

#define commonPin 27
#define pumpPin 14
#define section0 32
#define section1 33
#define section2 25
#define section3 26

void initSections();
byte getSectionPin(byte sectionNum);
void digiWrite(byte pin, bool stt);
void activateSection(byte sectionNum);
void deactivateAllSections();


#endif