#include "sections.h"

void initSections()
{
    pinMode(commonPin, OUTPUT);
    pinMode(pumpPin, OUTPUT);
    for(int i = 0; i < numOfSections; i++)
    {
        pinMode(getSectionPin(i), OUTPUT);
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
