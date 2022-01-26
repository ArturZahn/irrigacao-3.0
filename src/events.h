#ifndef EVENTS_H
#define EVENTS_H

#include <Arduino.h>
#include "programations.h"

void checkEvents(int *now);
byte findProgramationToStartNow(int *now);

#define subprogramationDurationMultiplier 60000 //in minutes
// #define subprogramationDurationMultiplier 1000 //in seconds

class eventClass
{
    private:

    bool isThereEventRunning;
    Programation activeProgamation;

    byte subprogramationCurrentStage;
    unsigned long durationOfCurrentStage;
    unsigned long stageStartTime;

    void setupNewEvent();
    unsigned long getDurationOfCurrentStage();
    void changeToNextStage();
    void setupCurrentStage();
    void triggerStartOfCurrentSubprogramation();
    void triggerEndOfCurrentSubprogramation();

    public:

    eventClass();
    void start(Programation programationToStart);
    // bool isEventRunning();
    void handle();
    void stopEvent();


};

void handleActiveEvent();
void startEvent(byte programationToStart);
void stopEvent();

#endif