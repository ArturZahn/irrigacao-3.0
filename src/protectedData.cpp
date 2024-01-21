#include "protectedData.h"

protectedData d;

/*---------------------- EEPROM ----------------------*/

void initializeEEPROM()
{
    if(!EEPROM.begin(EEPROM_SIZE)) LOGprintln("failed to initialise EEPROM");
    else LOGprintln("EEPROM initialized");
}

void storeEEPROMData()
{
    writeAnything(d);
    EEPROM.commit();
}

template <typename T> 
unsigned int writeAnything(const T& value)
{
    const byte * p = (const byte*) &value;
    unsigned int i;
    for (i = 0; i < sizeof value; i++)
    {
        // the update function only writes to eeprom if the value it's writting is diferent from what's written
        // EEPROM.update(i, *p++);

        // this emulated EEPROM library does not have the method update, but as it isnt an real EEPROM, its all right not to use the update method
        EEPROM.write(i, *p++);
    }
    return i;
} 

void readEEPROMData()
{
    readAnything(d);
}

template <typename T>
unsigned int readAnything(T& value)
{
    byte * p = (byte*) &value;
    unsigned int i;
    for (i = 0; i < sizeof value; i++)
    {
        *p++ = EEPROM.read(i);
    }
    return i;
}