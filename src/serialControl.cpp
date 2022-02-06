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
                runCommand();
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
                    Serial.print("\nError, command exceeds the ");
                    Serial.print(sizeOfCommand);
                    Serial.println(" characters limit");
                    
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

void runCommand()
{
    String command = String(fullCommand);
    String args = "";

    int spcIdx = command.indexOf(F(" "));
    if(spcIdx != -1)
    {
        args = command.substring(spcIdx+1);
        command = command.substring(0, spcIdx);
    }

    
    if(command == F("mostrarProgramacoes")) showProgramations();
    
    else if(command == F("alterarProgramacao")) alterProgramation(args);

    // else if(command == F("mostrarHora")) Serial.println("showTime();"); //showTime();
    
    // else if(command == F("ajustarHora")) Serial.println("ajustTime(args);"); //ajustTime(args);
    
    else if(command == F("pausarProgramacoes")) pauseProgramations();
    
    else if(command == F("retomarProgramacoes")) resumeProgramations();
    
    // else if(command == F("mostrarSetorManual")) Serial.println("showManualSetor();"); //showManualSetor();
    
    // else if(command == F("alterarSetorManual")) Serial.println("alterManualSetor(args);"); //alterManualSetor(args);
    
    else if(command == F("dispararProgramacao")) startEvent(args.toInt());

    else if(command == F("reiniciar")) restartSystem();

    else if(command == F("wifi")) exeWifiCommand(args);

    // else if(command == F("mostrarErros")) Serial.println("showErrors();"); //showErrors();
    
    // else if(command == F("limparErros")) Serial.println("clearErrors();"); //clearErrors();
    
    else
    {
        Serial.print(F("Erro, comando '"));
        Serial.print(command);
        Serial.println(F("' não existe"));
    }
}