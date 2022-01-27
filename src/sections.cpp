#include "sections.h"

void initSections()
{
    pinMode(commonPin, OUTPUT);
    digiWrite(commonPin, LOW);
    pinMode(pumpPin, OUTPUT);
    digiWrite(pumpPin, LOW);

    for(int i = 0; i < numOfSections; i++)
    {
        pinMode(getSectionPin(i), OUTPUT);
        digiWrite(getSectionPin(i), LOW);
    }
}

byte getSectionPin(byte sectionNum)
{
    switch(sectionNum)
    {
        case 0:
            return section0;
            break;
        case 1:
            return section1;
            break;
        case 2:
            return section2;
            break;
        case 3:
            return section3;
            break;
        
        default:
            return 255;
            break;
    }
}

void digiWrite(byte pin, bool stt)
{
    switch(pin)
    {
        case commonPin:
        case pumpPin:
        case section0:
        case section1:
            stt = !stt;
        break;
    }

    digitalWrite(pin, stt);
}

void activateSection(byte sectionNum)
{
    deactivateAllSections();
    if(sectionNum >= numOfSections || sectionNum == sectionEmpty) return; // do not enable any section if sectionNum is invalid
    
    digiWrite(commonPin, HIGH);
    digiWrite(pumpPin, HIGH);
    digiWrite(getSectionPin(sectionNum), HIGH);
}

void deactivateAllSections()
{
    digiWrite(commonPin, LOW);
    digiWrite(pumpPin, LOW);
    for(int i = 0; i < numOfSections; i++)
    {
        digiWrite(getSectionPin(i), LOW);
    }
}
