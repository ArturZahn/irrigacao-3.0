#include "manualSection.h"

byte activeManualSection = sectionEmpty;

bool setDefaultManualSection(byte sectionNum)
{
    if(sectionNum != sectionEmpty && sectionNum >= numOfSections) return false;

    d.defaultManualSection = sectionNum;
    storeEEPROMData();
    setNeedToUpdate();
    return true;
}

byte getDefaultManualSection()
{
    return d.defaultManualSection;
}

bool activateManualSection(byte sectionNum)
{
    if(sectionNum == sectionEmpty || sectionNum >= numOfSections) return false;

    setAutomaticMode(false);
    activateSection(sectionNum);
    activeManualSection = sectionNum;
    setNeedToUpdate();

    return true;
}

void deactivateManualSection()
{
    setAutomaticMode(false);
    deactivateAllSections();
    activeManualSection = sectionEmpty;
    setNeedToUpdate();
}

byte getActiveManualSection()
{
    return activeManualSection;
}