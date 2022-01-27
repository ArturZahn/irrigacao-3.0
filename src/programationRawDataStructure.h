#ifndef PROGRAMATIONRAWDATASTRUCTURE_H
#define PROGRAMATIONRAWDATASTRUCTURE_H

#include <Arduino.h>

#define numOfStages 4

// #define statusBit 11 // 12th least significant (position 11)
#define statusBit 3

#define numOfTriggers 5

// #define memoryLossDetectionSequence 0xA
// #define memoryLossDetectionPos 12
// #define memoryLossDetectionMask 0xF

#define memoryLossDetectionSequence 0xA
#define memoryLossDetectionPos 4
#define memoryLossDetectionMask 0xF

#define maxDuration 65535

#define triggerEmpty timeEmpty

struct programationRawData {
    byte sectionsOrder[numOfStages]; // if sectionOrder number is equal to "sectionEmpty", it means that there isnt any section selected
    unsigned int duration[numOfStages];
    unsigned int trigger[numOfTriggers];
    byte statusAndMemoryLossDetectionSequence; // 4 most significant bits are used to detect memory loss
                                               // 4th least significant bit means status (0 → disabled 1 → enabled)
                                               // 1st to 3rd least significant bit are not used
};


#endif