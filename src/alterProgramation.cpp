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
        for(int j = 0; j < maxNumOfSubProgramations; j++)
        {
            Serial.print("{");
            Serial.print(getProgramation(i).getSection(j));
            Serial.print(", ");
            Serial.print(getProgramation(i).getTimePerSection(j));
            Serial.print("}");
        }
        Serial.print(F("-{"));
        bool first = true;
        for(int j = 0; j < maxNumOfActivationTimes; j++)
        {
            if(getProgramation(i).getActivationTime(j) <= timeMax)
            {
                if(first) first = false;
                else Serial.print(", ");
                byte minutes = getProgramation(i).getActivationTime(j)%60;
                Serial.print((getProgramation(i).getActivationTime(j)-minutes)/60);
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
    // temporary data
    byte orderT[maxNumOfSubProgramations];
    int triggersT[maxNumOfActivationTimes];
    byte durationsT[maxNumOfSubProgramations];
    for(byte i = 0; i < maxNumOfActivationTimes; i++) triggersT[i] = 1500;
    bool enabledT;
    
    args.replace(F(" "), F(""));
    byte programIdx;
    
    int thingIdx = args.indexOf(F("->"));
    
    if(thingIdx == -1)
    {
        Serial.println(F("Erro, seta '->' não encontrada"));
        return;
    }
    
    programIdx = ajustMax(byte(args.substring(0, thingIdx).toInt()), 255);
    args = args.substring(thingIdx+2);
    
    if(programIdx >= numOfProgramations)
    {
        Serial.print(F("Erro, programacão "));
        Serial.print(String(byte(programIdx)));
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

    if(argsTemp == F("L") || argsTemp == F("l")) enabledT = true;
    else if(argsTemp == F("D") || argsTemp == F("d")) enabledT = false;
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
        if(count >= maxNumOfActivationTimes)
        {
            Serial.print(F("Erro, apenas "));
            Serial.print(String(maxNumOfActivationTimes));
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
        
        triggersT[count] = (thisArg.substring(0, thingIdx).toInt()*60)+thisArg.substring(thingIdx+1).toInt();
        
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
        orderT[count] = ajustMax(thisArg.substring(0, thingIdx).toInt(), 255);
        
        if(orderT[count] >= numOfSections && orderT[count] != sectionEmpty)
        {
            Serial.print(F("Erro, setor "));
            Serial.print(String(orderT[count]));
            Serial.println(F(" não existe"));
            return;
        }

        durationsT[count] = orderT[count]!=0?ajustMax(thisArg.substring(thingIdx+1).toInt(), 255):0;

        count++;
        thingIdx = args.indexOf(F(";"));
    }

    if(count != maxNumOfSubProgramations)
    {
        Serial.print(F("Erro, era esperado "));
        Serial.print(String(maxNumOfSubProgramations));
        Serial.print(F(" setores ("));
        Serial.print(String(count));
        Serial.println(F(" foram detectados)"));

        return;
    }
    Serial.print(F("Programação alterada: "));
    Serial.print(String(byte(programIdx)));
    Serial.print(F(" -> "));


    Serial.print(enabledT?F("L"):F("D"));
    getProgramation(programIdx).setStatus(enabledT);

    for(byte i = 0; i < maxNumOfSubProgramations; i++)
    {
        getProgramation(programIdx).setTimePerSection(i, durationsT[i]);
        getProgramation(programIdx).setSection(i, orderT[i]);

        Serial.print(F("{"));
        Serial.print(String(orderT[i]));
        Serial.print(F(", "));
        Serial.print(String(durationsT[i]));
        Serial.print(F("}"));
    }
    Serial.print(F("-{"));
    bool first = true;
    for(int i = 0; i < maxNumOfActivationTimes; i++)
    {
        getProgramation(programIdx).setActivationTime(i, triggersT[i]);
        if(triggersT[i] <= 1439)
        {
            if(first) first = false;
            else Serial.print(F(", "));
            byte minutes = triggersT[i]%60;
            Serial.print(String((triggersT[i]-minutes)/60));
            Serial.print(F(":"));
            Serial.print(String(minutes)+(minutes<10?F("0"):F("")));
        }
    }
    Serial.println(F("}"));
    
    storeEEPROMData();
}

byte ajustMax(int number, byte max)
{
  if(number >= max) return max;
  else return number;
}