#include "programations.h"

// Programation::Programation(){}

void Programation::setProgramationRawDataPointer(programationRawData *_rd)
{
    Programation::rawData = _rd;
    Programation::checkMemoryLossAndCorrect();
}

void Programation::checkMemoryLossAndCorrect()
{
    // if the memory loss detection sequence isnt right
    if((((*Programation::rawData).statusAndMemoryLossDetectionSequence>>memoryLossDetectionPos)&memoryLossDetectionMask) != memoryLossDetectionSequence)
    {
        // clear all data
        Programation::resetData();
        
        return;
    }
    

    Programation::checkIfTriggerIsValid();
    
}

void Programation::resetData()
{
    for(byte i = 0; i < numOfStages; i++)
    {
        (*Programation::rawData).sectionsOrder[i] = sectionEmpty;
        (*Programation::rawData).duration[i] = 0;
    }

    (*Programation::rawData).statusAndMemoryLossDetectionSequence = (memoryLossDetectionSequence<<memoryLossDetectionPos);
}

void Programation::setSectionOrder(byte stageNum, byte sectionOrderNum)
{
    (*Programation::rawData).sectionsOrder[stageNum] = sectionOrderNum;
}

void Programation::setDuration(byte stageNum, unsigned int duration)
{
    (*Programation::rawData).duration[stageNum] = duration;
}

void Programation::setStatus(bool stt)
{
    bitWrite((*Programation::rawData).statusAndMemoryLossDetectionSequence, statusBit, stt);
}

void Programation::setTrigger(byte triggerNum, int trigger)
{
    (*Programation::rawData).trigger[triggerNum] = trigger;

    Programation::checkIfTriggerIsValid();
}

byte Programation::getSectionOrder(byte stageNum)
{
    return (*Programation::rawData).sectionsOrder[stageNum];
}

unsigned int Programation::getDuration(byte stageNum)
{
    return (*Programation::rawData).duration[stageNum];
}

bool Programation::getStatus()
{
    return bitRead((*Programation::rawData).statusAndMemoryLossDetectionSequence, statusBit);
}

int Programation::getTrigger(byte triggerNum)
{
    return (*Programation::rawData).trigger[triggerNum];
}

void Programation::checkIfTriggerIsValid()
{
    for(byte i = 0; i < numOfTriggers; i++)
    {
        int actTm = Programation::getTrigger(i);
        if(actTm > timeMax && actTm != triggerEmpty)
        {
            Programation::setTrigger(i, triggerEmpty);
        }
    }
    
}

bool Programation::isNow(int *now)
{
    for(byte i = 0; i < numOfTriggers; i++)
    {
        int actTm = Programation::getTrigger(i);
        if(actTm != triggerEmpty && actTm == *now) return true;
    }
    return false;
}

void Programation::fireStartOfStage(byte stageNum)
{
    activateSection(Programation::getSectionOrder(stageNum));
}

void Programation::fireEndOfStage(byte stageNum)
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