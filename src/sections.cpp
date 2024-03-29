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
        case section0:
        case section1:
        case section2:
        case section3:
            stt = !stt;
        break;
    }

    digitalWrite(pin, stt);
}

void activateSection(byte sectionNum)
{
    deactivateAllSections();
    if(sectionNum >= numOfSections || sectionNum == sectionEmpty) return; // do not enable any section if sectionNum is invalid
    
    #ifdef enableAllSectionsWhenOneIsActivated
    if(d.areProgramationsPaused)
    {
        digiWrite(getSectionPin(0), HIGH);
        digiWrite(getSectionPin(1), HIGH);
        digiWrite(getSectionPin(2), HIGH);
        digiWrite(getSectionPin(3), HIGH);

        digiWrite(getSectionPin(sectionNum), HIGH);
        digiWrite(commonPin, HIGH);
    }
    else
    {
        digiWrite(getSectionPin(sectionNum), HIGH);
        digiWrite(pumpPin, HIGH);
        digiWrite(commonPin, HIGH);
    }
    #else
    digiWrite(getSectionPin(sectionNum), HIGH);
    digiWrite(pumpPin, HIGH);
    digiWrite(commonPin, HIGH);
    #endif
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
