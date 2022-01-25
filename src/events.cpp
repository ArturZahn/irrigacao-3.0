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

    // Serial.print("sections: ");
    // Serial.print(eventClass::activeProgamation.getSection(0));
    // Serial.print("|");
    // Serial.print(eventClass::activeProgamation.getSection(1));
    // Serial.print("|");
    // Serial.print(eventClass::activeProgamation.getSection(2));
    // Serial.print("|");
    // Serial.println(eventClass::activeProgamation.getSection(3));
    
    // Serial.print("durations: ");
    // Serial.print(eventClass::activeProgamation.getTimePerSection(0));
    // Serial.print("|");
    // Serial.print(eventClass::activeProgamation.getTimePerSection(1));
    // Serial.print("|");
    // Serial.print(eventClass::activeProgamation.getTimePerSection(2));
    // Serial.print("|");
    // Serial.print(eventClass::activeProgamation.getTimePerSection(3));


}

void eventClass::setupNewEvent()
{
    eventClass::isThereEventRunning = true;
    eventClass::subprogramationCurrentStage = 0;

    eventClass::setupCurrentStage();
}

unsigned long eventClass::getDurationOfCurrentStage()
{
    return eventClass::activeProgamation.getTimePerSection(eventClass::subprogramationCurrentStage) * subprogramationDurationMultiplier;
}

void eventClass::handle()
{
    if(eventClass::isThereEventRunning)
    {
        if(millis() - eventClass::stageStartTime > eventClass::durationOfCurrentStage)
        {
            eventClass::triggerEndOfCurrentSubprogramation();
            eventClass::changeToNextStage();
        }
    }
}

void eventClass::triggerStartOfCurrentSubprogramation()
{
    Serial.print("Start of subprogramation ");
    Serial.println(eventClass::subprogramationCurrentStage);
    eventClass::activeProgamation.triggerStartOfSubprogramation(eventClass::subprogramationCurrentStage);
}

void eventClass::triggerEndOfCurrentSubprogramation()
{
    Serial.print("End of subprogramation ");
    Serial.println(eventClass::subprogramationCurrentStage);
    eventClass::activeProgamation.triggerEndOfSubprogramation(eventClass::subprogramationCurrentStage);
}

void eventClass::changeToNextStage()
{
    eventClass::subprogramationCurrentStage++;

    if(eventClass::subprogramationCurrentStage == maxNumOfSubProgramations)
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

    eventClass::triggerStartOfCurrentSubprogramation();
}

void eventClass::stopEvent()
{
    eventClass::isThereEventRunning = false;
    eventClass::subprogramationCurrentStage = 0;
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