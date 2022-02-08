#ifndef EVENTS_H
#define EVENTS_H

#include <Arduino.h>
#include "programations.h"
#include "automaticMode.h"

void checkEvents(int *now);
byte findProgramationToStartNow(int *now);

#define stageDurationMultiplier 60000 //in minutes
// #define stageDurationMultiplier 1000 //in seconds

class eventClass
{
    private:

    bool isThereEventRunning;
    Programation activeProgamation;
    byte activeProgamationNum;

    byte stagesCurrentStage;
    unsigned long durationOfCurrentStage;
    unsigned long stageStartTime;

    void setupNewEvent();
    unsigned long getDurationOfCurrentStage();
    void changeToNextStage();
    void setupCurrentStage();
    void fireStartOfCurrentStage();
    void fireEndOfCurrentStage();

    public:

    eventClass();
    void start(Programation programationToStart);
    bool start(byte programationNumToStart);
    // bool isEventRunning();
    void handle();
    void stopEvent();
    byte getActiveProgramation();

};

void handleActiveEvent();
bool startEvent(byte programationToStart);
void stopEvent();
byte getActiveProgramation();

#endif