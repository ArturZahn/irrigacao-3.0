#include "programations.h"

// Programation::Programation(){}

void Programation::setProgramationRawDataPointer(programationRawData *_rd)
{
    Programation::rawData = _rd;
    Programation::checkMemoryLossAndCorrect();
}

void Programation::checkMemoryLossAndCorrect()
{
    // get statusAndActivationTime value:
    // (*Programation::rawData).statusAndActivationTime 

    // shift it
    // (*Programation::rawData).statusAndActivationTime>>memoryLossDetectionPos

    // select just the right bits
    // ((*Programation::rawData).statusAndActivationTime>>memoryLossDetectionPos)&memoryLossDetectionMask

    // check if its different than the defined sequence
    // (((*Programation::rawData).statusAndActivationTime>>memoryLossDetectionPos)&memoryLossDetectionMask) != memoryLossDetectionSequence

    

    // if the memory loss detection sequence isnt right (how does this 'if' work? look above)
    // if((((*Programation::rawData).statusAndActivationTime>>memoryLossDetectionPos)&memoryLossDetectionMask) != memoryLossDetectionSequence)

    // (*Programation::rawData).statusAndMemoryLossDetectionSequence = 0xA0;

    // Serial.println("extracting: ");
    // Serial.println((*Programation::rawData).statusAndMemoryLossDetectionSequence, BIN);
    // Serial.println((*Programation::rawData).statusAndMemoryLossDetectionSequence>>memoryLossDetectionPos, BIN);
    // Serial.println(((*Programation::rawData).statusAndMemoryLossDetectionSequence>>memoryLossDetectionPos)&memoryLossDetectionMask, BIN);
    // Serial.println("result: ");
    // Serial.println((((*Programation::rawData).statusAndMemoryLossDetectionSequence>>memoryLossDetectionPos)&memoryLossDetectionMask) == memoryLossDetectionSequence, BIN);


    // if the memory loss detection sequence isnt right
    if((((*Programation::rawData).statusAndMemoryLossDetectionSequence>>memoryLossDetectionPos)&memoryLossDetectionMask) != memoryLossDetectionSequence)
    {
        // clear all data
        Programation::resetData();
        
        return;
    }
    

    Programation::checkIfActivationTimeIsValid();
    
}

void Programation::resetData()
{
    for(byte i = 0; i < maxNumOfSubProgramations; i++)
    {
        (*Programation::rawData).sections[i] = sectionEmpty;
        (*Programation::rawData).timePerSection[i] = 0;
    }

    // (*Programation::rawData).statusAndActivationTime = (memoryLossDetectionSequence<<memoryLossDetectionPos)|activationTimeEmpty;
    (*Programation::rawData).statusAndMemoryLossDetectionSequence = (memoryLossDetectionSequence<<memoryLossDetectionPos);
}

void Programation::setSection(byte subProgramationNum, byte sectionNum)
{
    (*Programation::rawData).sections[subProgramationNum] = sectionNum;
}

void Programation::setTimePerSection(byte subProgramationNum, unsigned int timePerSection)
{
    (*Programation::rawData).timePerSection[subProgramationNum] = timePerSection;
}

void Programation::setStatus(bool stt)
{
    // bitWrite((*Programation::rawData).statusAndActivationTime, statusBit, stt);
    bitWrite((*Programation::rawData).statusAndMemoryLossDetectionSequence, statusBit, stt);
}

void Programation::setActivationTime(byte activationTimeNum, int activationTime)
{
    // (*Programation::rawData).statusAndActivationTime &= ~activationTimeMask;
    // (*Programation::rawData).statusAndActivationTime |= activationTime&activationTimeMask;

    (*Programation::rawData).activationTime[activationTimeNum] = activationTime;

    Programation::checkIfActivationTimeIsValid();
}

byte Programation::getSection(byte subProgramationNum)
{
    return (*Programation::rawData).sections[subProgramationNum];
}

unsigned int Programation::getTimePerSection(byte subProgramationNum)
{
    return (*Programation::rawData).timePerSection[subProgramationNum];
}

bool Programation::getStatus()
{
    // just get the 5th most significant bit of rawData.statusAndActivationTime
    // return bitRead((*Programation::rawData).statusAndActivationTime, statusBit);
    return bitRead((*Programation::rawData).statusAndMemoryLossDetectionSequence, statusBit);
}

int Programation::getActivationTime(byte activationTimeNum)
{
    return (*Programation::rawData).activationTime[activationTimeNum];
}

void Programation::checkIfActivationTimeIsValid()
{
    for(byte i = 0; i < maxNumOfActivationTimes; i++)
    {
        int actTm = Programation::getActivationTime(i);
        if(actTm > timeMax && actTm != activationTimeEmpty)
        {
            Programation::setActivationTime(i, activationTimeEmpty);
        }
    }
    
}

bool Programation::isNow(int *now)
{
    for(byte i = 0; i < maxNumOfActivationTimes; i++)
    {
        int actTm = Programation::getActivationTime(i);
        if(actTm != activationTimeEmpty && actTm == *now) return true;
    }
    // return Programation::getActivationTime() == 
    return false;
}

void Programation::triggerStartOfSubprogramation(byte subprogramationNum)
{
    activateSection(Programation::getSection(subprogramationNum));
}

void Programation::triggerEndOfSubprogramation(byte subprogramationNum)
{
    deactivateAllSections();
}


///////////////////////////////////////////////////////////////

Programation programations[numOfProgramations];

void initializeProgramations()
{
    for(byte i = 0; i < numOfProgramations; i++)
    {
        programations[i].setProgramationRawDataPointer(&d.programationsRawData[i]);
    }
}

Programation getProgramation(byte programationNum)
{
    return programations[programationNum];
}