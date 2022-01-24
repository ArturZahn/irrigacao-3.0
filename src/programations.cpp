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
    if((((*Programation::rawData).statusAndActivationTime>>memoryLossDetectionPos)&memoryLossDetectionMask) != memoryLossDetectionSequence)
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
    (*Programation::rawData).statusAndActivationTime = (memoryLossDetectionSequence<<memoryLossDetectionPos)|activationTimeEmpty;
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
    bitWrite((*Programation::rawData).statusAndActivationTime, statusBit, stt);
}

void Programation::setActivationTime(int activationTime)
{
    (*Programation::rawData).statusAndActivationTime &= ~activationTimeMask;
    (*Programation::rawData).statusAndActivationTime |= activationTime&activationTimeMask;

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
    // return bitRead(rawData.statusAndActivationTime, statusBit);
    return bitRead((*Programation::rawData).statusAndActivationTime, statusBit);
}

int Programation::getActivationTime()
{
    return (*Programation::rawData).statusAndActivationTime&activationTimeMask;
}

void Programation::checkIfActivationTimeIsValid()
{
    int actTm = Programation::getActivationTime();
    if(actTm > timeMax && actTm != activationTimeEmpty)
    {

        Serial.print("setting:");
        Serial.println(activationTimeEmpty);
        Programation::setActivationTime(activationTimeEmpty);
        
    }
    
}

bool Programation::isNow()
{
    return Programation::getActivationTime() == getDayTime();
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