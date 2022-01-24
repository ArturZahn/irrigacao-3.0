#ifndef PROGRAMATIONS_H
#define PROGRAMATIONS_H

#include <Arduino.h>
#include "protectedData.h"

#define programationEmpty 255

class Programation
{
    private:

    public:

        programationRawData *rawData;

        // Programation();

        void setProgramationRawDataPointer(programationRawData *_rd);

        void checkMemoryLossAndCorrect();
        void resetData();

        void setSection(byte subProgramationNum, byte sectionNum);
        void setTimePerSection(byte subProgramationNum, unsigned int timePerSection);
        void setStatus(bool stt);
        void setActivationTime(int activationTime);

        byte getSection(byte subProgramationNum);
        unsigned int getTimePerSection(byte subProgramationNum);
        bool getStatus();
        int getActivationTime();

        void checkIfActivationTimeIsValid();

        bool isNow();
};

void initializeProgramations();
Programation getProgramation(byte programationNum);

extern Programation programations[numOfProgramations];

#endif