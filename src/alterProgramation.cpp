#include "alterProgramation.h"

void showProgramations()
{
    Serial.println("status:");
    for(byte prog = 0; prog < numOfProgramations; prog++)
    {
        Serial.print(getProgramation(prog).getStatus(), BIN);
        Serial.print(" ");
    }
    Serial.println();
    
    Serial.println(F("Programações:"));
    for(int i = 0; i < numOfProgramations; i++)
    {
        Serial.print(i);
        Serial.print(F(" -> "));
        Serial.print(getProgramation(i).getStatus()?F("L"):F("D"));
        for(int j = 0; j < numOfStages; j++)
        {
            Serial.print("{");
            Serial.print(getProgramation(i).getSectionOrder(j));
            Serial.print(", ");
            Serial.print(getProgramation(i).getDuration(j));
            Serial.print("}");
        }
        Serial.print(F("-{"));
        bool first = true;
        for(int j = 0; j < numOfTriggers; j++)
        {
            if(getProgramation(i).getTrigger(j) <= timeMax)
            {
                if(first) first = false;
                else Serial.print(", ");
                byte minutes = getProgramation(i).getTrigger(j)%60;
                Serial.print((getProgramation(i).getTrigger(j)-minutes)/60);
                Serial.print(F(":"));
                if(minutes < 10) Serial.print(F("0"));
                Serial.print(minutes);
            }
        }
        Serial.println(F("}"));
    }
    Serial.print(F("\n"));
}

void alterProgramation(String &args)
{
    programationRawData tempProgRawData;
    Programation tempProg;
    tempProg.setProgramationRawDataPointer(&tempProgRawData);
    
    args.replace(F(" "), F(""));
    byte programationIdx;
    
    //this ↓ variable will be used for storing the index of many things
    int thingIdx = args.indexOf(F("->"));
    
    if(thingIdx == -1)
    {
        Serial.println(F("Erro, seta '->' não encontrada"));
        return;
    }
    
    programationIdx = args.substring(0, thingIdx).toInt();
    args = args.substring(thingIdx+2);
    
    if(programationIdx >= numOfProgramations)
    {
        Serial.print(F("Erro, programacão "));
        Serial.print(String(byte(programationIdx)));
        Serial.println(F(" não existe"));
        return;
    }

    thingIdx = args.indexOf(F("{"));
    if(thingIdx == -1)
    {
        Serial.println(F("Erro, primeira chave '{' não encontrada"));
        return;
    }
    String argsTemp = args.substring(0, thingIdx);
    args = args.substring(thingIdx);

    if(argsTemp == F("L") || argsTemp == F("l")) tempProg.setStatus(true);
    else if(argsTemp == F("D") || argsTemp == F("d")) tempProg.setStatus(false);
    else
    {
        Serial.print(F("Erro, "));
        if(argsTemp == "") Serial.print(F("o estado da programação não foi encontrado"));
        else
        {
            Serial.print("'");
            Serial.print(String(argsTemp));
            Serial.print(F("' não é um estado válido"));
        }
        Serial.println(F(" (esperado 'L' ligado ou 'D' desligado"));
        return;
    }

    thingIdx = args.indexOf("-");
    if(thingIdx == -1)
    {
        Serial.println(F("Erro, traco '-' não encontrado"));
        return;
    }
    argsTemp = args.substring(thingIdx+1);
    args = args.substring(0, thingIdx);
    
    argsTemp.replace(F("{}"), F(""));
    argsTemp.replace(F("{"), F(""));
    argsTemp.replace(F("}"), F(","));
    
    String thisArg;
    byte count = 0;
    thingIdx = argsTemp.indexOf(F(","));
    while(thingIdx != -1)
    {
        if(count >= numOfTriggers)
        {
            Serial.print(F("Erro, apenas "));
            Serial.print(String(numOfTriggers));
            Serial.print(F(" horários são permitidos ("));
            Serial.print(String(count+1));
            Serial.println(F(" foram detectados)"));
            return;
        }
        
        thisArg = argsTemp.substring(0, thingIdx);
        argsTemp = argsTemp.substring(thingIdx+1);

        thingIdx = thisArg.indexOf(F(":"));
        if(thingIdx == -1)
        {
            Serial.println(F("Erro, algum horário não foi informado corretamente"));
            return;
        }
        
        tempProg.setTrigger(count, (thisArg.substring(0, thingIdx).toInt()*60)+thisArg.substring(thingIdx+1).toInt());
        count++;
        thingIdx = argsTemp.indexOf(F(","));
    }
    
    args.replace(F("}{"), F(";"));
    args.replace(F("}"), F(";"));
    args.replace(F("{"), F(""));
    
    thingIdx = args.indexOf(F(";"));
    count = 0;
    while(thingIdx != -1)
    {
        thisArg = args.substring(0, thingIdx);
        args = args.substring(thingIdx+1);

        thingIdx = thisArg.indexOf(F(","));
        if(thingIdx == -1)
        {
            Serial.println(F("Erro, algum setor não foi informado corretamente"));
            return;
        }
        tempProg.setSectionOrder(count, thisArg.substring(0, thingIdx).toInt());
        
        if(tempProg.getSectionOrder(count) >= numOfSections && tempProg.getSectionOrder(count) != sectionEmpty)
        {
            Serial.print(F("Erro, setor "));
            Serial.print(String(tempProg.getSectionOrder(count)));
            Serial.println(F(" não existe"));
            return;
        }

        tempProg.setDuration(count, ajustMaxuint(thisArg.substring(thingIdx+1).toInt(), maxDuration));

        count++;
        thingIdx = args.indexOf(F(";"));
    }

    if(count != numOfStages)
    {
        Serial.print(F("Erro, era esperado "));
        Serial.print(String(numOfStages));
        Serial.print(F(" setores ("));
        Serial.print(String(count));
        Serial.println(F(" foram detectados)"));

        return;
    }
    Serial.print(F("Programação alterada: "));
    Serial.print(String(byte(programationIdx)));
    Serial.print(F(" -> "));


    Serial.print(tempProg.getStatus()?F("L"):F("D"));
    getProgramation(programationIdx).setStatus(tempProg.getStatus());

    for(byte i = 0; i < numOfStages; i++)
    {
        getProgramation(programationIdx).setSectionOrder(i, tempProg.getSectionOrder(i));
        getProgramation(programationIdx).setDuration(i, tempProg.getDuration(i));

        Serial.print(F("{"));
        Serial.print(tempProg.getSectionOrder(i));
        Serial.print(F(", "));
        Serial.print(tempProg.getDuration(i));
        Serial.print(F("}"));
    }
    Serial.print(F("-{"));
    bool first = true;
    for(int i = 0; i < numOfTriggers; i++)
    {
        getProgramation(programationIdx).setTrigger(i, tempProg.getTrigger(i));
        if(tempProg.getTrigger(i) <= 1439)
        {
            if(first) first = false;
            else Serial.print(F(", "));
            byte minutes = tempProg.getTrigger(i)%60;
            Serial.print(String((tempProg.getTrigger(i)-minutes)/60));
            Serial.print(F(":"));
            Serial.print(String(minutes)+(minutes<10?F("0"):F("")));
        }
    }
    Serial.println(F("}"));
    
    storeEEPROMData();
}

unsigned int ajustMaxuint(int number, unsigned int max)
{
  if(number >= max) return max;
  else return number;
}