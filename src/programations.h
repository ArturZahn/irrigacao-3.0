#ifndef PROGRAMATIONS_H
#define PROGRAMATIONS_H

#include <Arduino.h>
#include "protectedData.h"
#include "sections.h"
#include "timeFuncs.h"

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

        void setSectionOrder(byte stageNum, byte sectionOrderNum);
        void setDuration(byte stageNum, unsigned int duration);
        void setStatus(bool stt);
        void setTrigger(byte triggerNum, int trigger);

        byte getSectionOrder(byte stageNum);
        unsigned int getDuration(byte stageNum);
        bool getStatus();
        int getTrigger(byte triggerNum);

        void fireStartOfStage(byte stageNum);
        void fireEndOfStage(byte stageNum);

        void checkIfTriggerIsValid();

        bool isNow(int *now);
};

void initializeProgramations();
Programation getProgramation(byte programationNum);

extern Programation programations[numOfProgramations];

#endif