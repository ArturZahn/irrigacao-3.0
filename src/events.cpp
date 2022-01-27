#include "events.h"

void checkEvents(int *now)
{
    // Serial.println("checking events...");

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

    // Serial.print("sections order: ");
    // Serial.print(eventClass::activeProgamation.getSectionOrder(0));
    // Serial.print("|");
    // Serial.print(eventClass::activeProgamation.getSectionOrder(1));
    // Serial.print("|");
    // Serial.print(eventClass::activeProgamation.getSectionOrder(2));
    // Serial.print("|");
    // Serial.println(eventClass::activeProgamation.getSectionOrder(3));
    
    // Serial.print("durations: ");
    // Serial.print(eventClass::activeProgamation.getDuration(0));
    // Serial.print("|");
    // Serial.print(eventClass::activeProgamation.getDuration(1));
    // Serial.print("|");
    // Serial.print(eventClass::activeProgamation.getDuration(2));
    // Serial.print("|");
    // Serial.print(eventClass::activeProgamation.getDuration(3));


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
    Serial.print("Start of stage ");
    Serial.println(eventClass::stagesCurrentStage);
    eventClass::activeProgamation.fireStartOfStage(eventClass::stagesCurrentStage);
}

void eventClass::fireEndOfCurrentStage()
{
    Serial.print("End of stage ");
    Serial.println(eventClass::stagesCurrentStage);
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

void startEvent(byte programationNumToStart)
{
    activeEvent.start(getProgramation(programationNumToStart));
}

void handleActiveEvent()
{
    activeEvent.handle();
}

void stopEvent()
{
    activeEvent.stopEvent();
}