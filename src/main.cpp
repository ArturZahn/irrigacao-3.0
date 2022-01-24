#include <Arduino.h>
#include "watchTime.h"
#include "programations.h"


void setup()
{
    Serial.begin(115200);

    initializeEEPROM();
    
    readEEPROMData();
    Serial.println("EEPROM data read");
    initializeProgramations();
    Serial.println("Programations initialized");
}

void loop()
{
    handdleWatchTime();
    
//     d.programationsRawData->statusAndActivationTime += 1;
}












// /*
//    EEPROM Write

//    Stores random values into the EEPROM.
//    These values will stay in the EEPROM when the board is
//    turned off and may be retrieved later by another sketch.
// */

// #include "EEPROM.h"

// // the current address in the EEPROM (i.e. which byte we're going to write to next)
// int addr = 0;
// #define EEPROM_SIZE 64
// void setup()
// {
//     Serial.begin(115200);
//     Serial.println("start...");
//     if (!EEPROM.begin(EEPROM_SIZE))
//     {
//         Serial.println("failed to initialise EEPROM"); delay(1000000);
//     }

//     Serial.print("\n\nlast: ");
//     Serial.println(byte(EEPROM.read(addr)));
  
//     int val = byte(random(10020));
//     EEPROM.write(addr, val);
//     Serial.print("writing: ");
//     Serial.println(val);
//     EEPROM.commit();

//     Serial.print("reading: ");
//     Serial.println(byte(EEPROM.read(addr)));
// }

// void loop()
// {
// }
