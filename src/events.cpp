#include "events.h"


void checkEvents(int *now)
{
    // LOGprintln("checking events...");

    byte programationNumToStart = findProgramationToStartNow(now);
    if(programationNumToStart != programationEmpty)
    {
        startEvent(programationNumToStart);
    }
}

byte findProgramationToStartNow(int *now)
{
    for(int i = 0; i < numOfProgramations; i++)
    {
        if(programations[i].getStatus())
        {
            if(programations[i].isNow(now))
            {
                return i;
            }
        }
    }

    return programationEmpty;
}

eventClass::eventClass()
{
    eventClass::isThereEventRunning = false;
}

void eventClass::start(Programation programationToStart)
{
    setAutomaticMode(true);
    if(eventClass::isThereEventRunning)
    {
        eventClass::stopEvent();
    }

    eventClass::activeProgamation = programationToStart;
    eventClass::setupNewEvent();

    setNeedToUpdate();
}

bool eventClass::start(byte programationNumToStart)
{
    if(programationNumToStart == programationEmpty || programationNumToStart >= numOfProgramations) return false;

    eventClass::start(getProgramation(programationNumToStart));
    eventClass::activeProgamationNum = programationNumToStart;
    
    
    return true;
}

void eventClass::setupNewEvent()
{
    eventClass::isThereEventRunning = true;
    eventClass::stagesCurrentStage = 0;

    eventClass::setupCurrentStage();
}

unsigned long eventClass::getDurationOfCurrentStage()
{
    return eventClass::activeProgamation.getDuration(eventClass::stagesCurrentStage) * stageDurationMultiplier;
}

void eventClass::handle()
{
    if(eventClass::isThereEventRunning)
    {
        if(millis() - eventClass::stageStartTime > eventClass::durationOfCurrentStage)
        {
            eventClass::fireEndOfCurrentStage();
            eventClass::changeToNextStage();
        }
    }
}

void eventClass::fireStartOfCurrentStage()
{
    LOGprint("Start of stage ");
    LOGprintln(eventClass::stagesCurrentStage);
    eventClass::activeProgamation.fireStartOfStage(eventClass::stagesCurrentStage);
}

void eventClass::fireEndOfCurrentStage()
{
    LOGprint("End of stage ");
    LOGprintln(eventClass::stagesCurrentStage);
    eventClass::activeProgamation.fireEndOfStage(eventClass::stagesCurrentStage);
}

void eventClass::changeToNextStage()
{
    eventClass::stagesCurrentStage++;

    if(eventClass::stagesCurrentStage == numOfStages)
    {
        // there is no next programation stage
        eventClass::stopEvent();
        return;
    }

    eventClass::setupCurrentStage();
}

void eventClass::setupCurrentStage()
{
    durationOfCurrentStage = eventClass::getDurationOfCurrentStage();
    eventClass::stageStartTime = millis();

    eventClass::fireStartOfCurrentStage();
}

void eventClass::stopEvent()
{
    setAutomaticMode(true);
    eventClass::isThereEventRunning = false;
    eventClass::stagesCurrentStage = 0;
    eventClass::durationOfCurrentStage = 0;
    eventClass::activeProgamationNum = programationEmpty;
    setNeedToUpdate();
}

byte eventClass::getActiveProgramation()
{
    if(!eventClass::isThereEventRunning) return programationEmpty;

    return eventClass::activeProgamationNum;
}

eventClass activeEvent;

bool startEvent(byte programationNumToStart)
{
    return activeEvent.start(programationNumToStart);
}

void handleActiveEvent()
{
    activeEvent.handle();
}

void stopEvent()
{
    activeEvent.stopEvent();
}

byte getActiveProgramation()
{
    return activeEvent.getActiveProgramation();
}