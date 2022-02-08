#include "automaticMode.h"

bool _isAutomaticModeEnabled = true;

bool isAutomaticModeEnabled()
{
    return _isAutomaticModeEnabled;
}

bool changingMode = false;
void setAutomaticMode(bool mode)
{
    if(changingMode) return;

    changingMode = true;

    if(_isAutomaticModeEnabled != mode)
    {
        _isAutomaticModeEnabled = mode;
        if(_isAutomaticModeEnabled) handleEnterAutomaticMode();
        else handleLeaveAutomaticMode();
    }
    
    changingMode = false;
}

void handleEnterAutomaticMode()
{
    deactivateManualSection();
}

void handleLeaveAutomaticMode()
{
    stopEvent();
    pauseAutomaticProgramations();
}