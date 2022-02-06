#include "main.h"

void setup()
{
    initPrint();
    initSections();
    initRTC();
    initializeEEPROM();
    readEEPROMData();
    initializeProgramations();
    initWifi();

    // for(byte prog = 0; prog < numOfProgramations; prog++)
    // {
        
    //     getProgramation(prog).setStatus(false);
    //     for(byte actTm = 0; actTm < numOfTriggers; actTm++)
    //     {
    //         getProgramation(prog).setTrigger(actTm, triggerEmpty);
    //         // getProgramation(prog).setTrigger(actTm, (prog+2)*100 + actTm*2);
    //     }
        
    //     for(byte subprogNum = 0; subprogNum < numOfStages; subprogNum++)
    //     {
    //         getProgramation(prog).setSectionOrder(subprogNum, sectionEmpty);
    //         getProgramation(prog).setDuration(subprogNum, 0);

    //         // getProgramation(prog).setSectionOrder(subprogNum, subprogNum+10);
    //         // getProgramation(prog).setDuration(subprogNum, (subprogNum*2)+10);
    //     }
    //     NBprintln("\n");
    // }

    // storeEEPROMData();
}

void loop()
{
    handleWatchTime();
    handleActiveEvent();
    handleSerialControl();
    handleWifi();
}