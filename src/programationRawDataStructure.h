#ifndef PROGRAMATIONRAWDATASTRUCTURE_H
#define PROGRAMATIONRAWDATASTRUCTURE_H

#include <Arduino.h>

#define maxNumOfSubProgramations 4

// #define statusBit 11 // 12th least significant (position 11)
#define statusBit 3

#define maxNumOfActivationTimes 5

// #define memoryLossDetectionSequence 0xA
// #define memoryLossDetectionPos 12
// #define memoryLossDetectionMask 0xF

#define memoryLossDetectionSequence 0xA
#define memoryLossDetectionPos 4
#define memoryLossDetectionMask 0xF

#define maxTimePerSection 65535

#define sectionEmpty 255
// #define activationTimeMask 0x7FF
#define activationTimeEmpty timeEmpty

struct programationRawData {
    byte sections[maxNumOfSubProgramations]; // if section number is equal to "sectionEmpty", it means that there isnt any section selected
    unsigned int timePerSection[maxNumOfSubProgramations];
    unsigned int activationTime[maxNumOfActivationTimes];
    byte statusAndMemoryLossDetectionSequence; // 4 most significant bits are used to detect memory loss
                                               // 4th least significant bit means status (0 → disabled 1 → enabled)
                                               // 1st to 3rd least significant bit are not used

    // int statusAndActivationTime; // 4 most significant bits are used to detect memory loss
    //                              // 12th least significant bit means status (0 → disabled 1 → enabled)
    //                              // 11 least bits are a number that represents the time of day (value of "activationTimeEmpty" means that its empty)
};


#endif