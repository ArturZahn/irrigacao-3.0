#ifndef PROGRAMATIONRAWDATASTRUCTURE_H
#define PROGRAMATIONRAWDATASTRUCTURE_H

#include <Arduino.h>

#define maxNumOfSectionsInprogramation 4
#define timeEmpty 0x7FF
#define memoryLossDetectionSequence 0xA
#define statusBit 11 // 12th least significant

struct programationRawData {
    byte sections[maxNumOfSectionsInprogramation]; 
    unsigned int timePer[maxNumOfSectionsInprogramation];
    int statusAndActivationTime; // 4 most significant bits are used to detect memory loss
                                 // 12th least significant bit means status (0 → disabled 1 → enabled)
                                 // 11 least bits are a number that represents the time of day (B111 1111 1111 or 0x59F means no time or "timeEmpty")
};


#endif