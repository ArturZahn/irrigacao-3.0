#include "events.h"

void checkEvents(int *now)
{
    // NBprintln("checking events...");

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

    if(eventClass::isThereEventRunning)
    {
        eventClass::stopEvent();
    }

    eventClass::activeProgamation = programationToStart;
    eventClass::setupNewEvent();

    // NBprint("sections order: ");
    // NBprint(eventClass::activeProgamation.getSectionOrder(0));
    // NBprint("|");
    // NBprint(eventClass::activeProgamation.getSectionOrder(1));
    // NBprint("|");
    // NBprint(eventClass::activeProgamation.getSectionOrder(2));
    // NBprint("|");
    // NBprintln(eventClass::activeProgamation.getSectionOrder(3));
    
    // NBprint("durations: ");
    // NBprint(eventClass::activeProgamation.getDuration(0));
    // NBprint("|");
    // NBprint(eventClass::activeProgamation.getDuration(1));
    // NBprint("|");
    // NBprint(eventClass::activeProgamation.getDuration(2));
    // NBprint("|");
    // NBprint(eventClass::activeProgamation.getDuration(3));


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
    NBprint("Start of stage ");
    NBprintln(eventClass::stagesCurrentStage);
    eventClass::activeProgamation.fireStartOfStage(eventClass::stagesCurrentStage);
}

void eventClass::fireEndOfCurrentStage()
{
    NBprint("End of stage ");
    NBprintln(eventClass::stagesCurrentStage);
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
    eventClass::isThereEventRunning = false;
    eventClass::stagesCurrentStage = 0;
    eventClass::durationOfCurrentStage = 0;
}

eventClass activeEvent;

bool startEvent(byte programationNumToStart)
{
    if(programationNumToStart == programationEmpty || programationNumToStart >= numOfProgramations) return false;

    activeEvent.start(getProgramation(programationNumToStart));
    return true;
}

void handleActiveEvent()
{
    activeEvent.handle();
}

void stopEvent()
{
    activeEvent.stopEvent();
}