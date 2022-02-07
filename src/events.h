#ifndef EVENTS_H
#define EVENTS_H

#include <Arduino.h>
#include "programations.h"

void checkEvents(int *now);
byte findProgramationToStartNow(int *now);

#define stageDurationMultiplier 60000 //in minutes
// #define stageDurationMultiplier 1000 //in seconds

class eventClass
{
    private:

    bool isThereEventRunning;
    Programation activeProgamation;

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
    // bool isEventRunning();
    void handle();
    void stopEvent();


};

void handleActiveEvent();
bool startEvent(byte programationToStart);
void stopEvent();

#endif