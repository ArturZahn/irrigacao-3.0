#include "serialControl.h"

char fullCommand[sizeOfCommand];
byte currentCarriagePos = 0;

void handleSerialControl()
{
    while(Serial.available())
    {
        char c = Serial.read();
        if(c != '\r')
        {
            switch (c)
            {
            case '\n':
                Serial.print("\r\n");
                runSerialCommand();
                clearCommand();
                break;

            case '\b': //backspace
                if(currentCarriagePos != 0)
                {
                    currentCarriagePos--;
                    fullCommand[currentCarriagePos] = '\0';
                    Serial.write(c); // send backspace
                    Serial.write(' ');
                    Serial.write(c); // send backspace
                }
                break;
            
            default:
                if(currentCarriagePos >= sizeOfCommand)
                {
                    Serial.println();
                    CMDprint("Error, command exceeds the ");
                    CMDprint(sizeOfCommand);
                    CMDprintln(" characters limit");
                    
                    clearCommand();
                }
                else
                {
                    fullCommand[currentCarriagePos] = c;
                    currentCarriagePos++;
                    Serial.write(c);
                }
                break;
            }
        }
    }
}

void clearCommand()
{
    memset(fullCommand, 0, sizeOfCommand);
    currentCarriagePos = 0;
}

void runSerialCommand()
{
    cliRunCommand(fullCommand, CLI_SOURCE_SERIAL);
}