#include "alterProgramation.h"

void showProgramations()
{
    setCmdState(true);
    CMDprintln("status:");
    for(byte prog = 0; prog < numOfProgramations; prog++)
    {
        CMDprint(getProgramation(prog).getStatus());
        CMDprint(" ");
    }
    CMDprintln();
    
    CMDprintln(F("Programações:"));
    for(int i = 0; i < numOfProgramations; i++)
    {
        CMDprint(i);
        CMDprint(F(" -> "));
        CMDprint(getProgramation(i).getStatus()?F("L"):F("D"));
        for(int j = 0; j < numOfStages; j++)
        {
            CMDprint("{");
            CMDprint(getProgramation(i).getSectionOrder(j));
            CMDprint(", ");
            CMDprint(getProgramation(i).getDuration(j));
            CMDprint("}");
        }
        CMDprint(F("-{"));
        bool first = true;
        for(int j = 0; j < numOfTriggers; j++)
        {
            if(getProgramation(i).getTrigger(j) <= timeMax)
            {
                if(first) first = false;
                else CMDprint(", ");
                byte minutes = getProgramation(i).getTrigger(j)%60;
                CMDprint((getProgramation(i).getTrigger(j)-minutes)/60);
                CMDprint(F(":"));
                if(minutes < 10) CMDprint(F("0"));
                CMDprint(minutes);
            }
        }
        CMDprintln(F("}"));
    }
    CMDprint(F("\n"));
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
        CMDprintln(F("Erro, seta '->' não encontrada"));
        return;
    }
    
    programationIdx = args.substring(0, thingIdx).toInt();
    args = args.substring(thingIdx+2);
    
    if(programationIdx >= numOfProgramations)
    {
        CMDprint(F("Erro, programacão "));
        CMDprint(String(byte(programationIdx)));
        CMDprintln(F(" não existe"));
        return;
    }

    thingIdx = args.indexOf(F("{"));
    if(thingIdx == -1)
    {
        CMDprintln(F("Erro, primeira chave '{' não encontrada"));
        return;
    }
    String argsTemp = args.substring(0, thingIdx);
    args = args.substring(thingIdx);

    if(argsTemp == F("L") || argsTemp == F("l")) tempProg.setStatus(true);
    else if(argsTemp == F("D") || argsTemp == F("d")) tempProg.setStatus(false);
    else
    {
        CMDprint(F("Erro, "));
        if(argsTemp == "") CMDprint(F("o estado da programação não foi encontrado"));
        else
        {
            CMDprint("'");
            CMDprint(String(argsTemp));
            CMDprint(F("' não é um estado válido"));
        }
        CMDprintln(F(" (esperado 'L' ligado ou 'D' desligado"));
        return;
    }

    thingIdx = args.indexOf("-");
    if(thingIdx == -1)
    {
        CMDprintln(F("Erro, traco '-' não encontrado"));
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
            CMDprint(F("Erro, apenas "));
            CMDprint(String(numOfTriggers));
            CMDprint(F(" horários são permitidos ("));
            CMDprint(String(count+1));
            CMDprintln(F(" foram detectados)"));
            return;
        }
        
        thisArg = argsTemp.substring(0, thingIdx);
        argsTemp = argsTemp.substring(thingIdx+1);

        thingIdx = thisArg.indexOf(F(":"));
        if(thingIdx == -1)
        {
            CMDprintln(F("Erro, algum horário não foi informado corretamente"));
            return;
        }
        
        tempProg.setTrigger(count, (thisArg.substring(0, thingIdx).toInt()*60)+thisArg.substring(thingIdx+1).toInt());

        count++;
        thingIdx = argsTemp.indexOf(F(","));
    }

    for(byte i = count; i < numOfTriggers; i++) tempProg.setTrigger(i, triggerEmpty);
    
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
            CMDprintln(F("Erro, algum setor não foi informado corretamente"));
            return;
        }
        tempProg.setSectionOrder(count, thisArg.substring(0, thingIdx).toInt());
        
        if(tempProg.getSectionOrder(count) >= numOfSections && tempProg.getSectionOrder(count) != sectionEmpty)
        {
            CMDprint(F("Erro, setor "));
            CMDprint(String(tempProg.getSectionOrder(count)));
            CMDprintln(F(" não existe"));
            return;
        }

        tempProg.setDuration(count, ajustMaxuint(thisArg.substring(thingIdx+1).toInt(), maxDuration));

        count++;
        thingIdx = args.indexOf(F(";"));
    }

    if(count != numOfStages)
    {
        CMDprint(F("Erro, era esperado "));
        CMDprint(String(numOfStages));
        CMDprint(F(" setores ("));
        CMDprint(String(count));
        CMDprintln(F(" foram detectados)"));

        return;
    }

    setCmdState(true);
    
    CMDprint(F("Programação alterada: "));
    CMDprint(String(byte(programationIdx)));
    CMDprint(F(" -> "));


    CMDprint(tempProg.getStatus()?F("L"):F("D"));
    getProgramation(programationIdx).setStatus(tempProg.getStatus());

    for(byte i = 0; i < numOfStages; i++)
    {
        getProgramation(programationIdx).setSectionOrder(i, tempProg.getSectionOrder(i));
        getProgramation(programationIdx).setDuration(i, tempProg.getDuration(i));

        CMDprint(F("{"));
        CMDprint(tempProg.getSectionOrder(i));
        CMDprint(F(", "));
        CMDprint(tempProg.getDuration(i));
        CMDprint(F("}"));
    }
    CMDprint(F("-{"));
    bool first = true;
    for(int i = 0; i < numOfTriggers; i++)
    {
        getProgramation(programationIdx).setTrigger(i, tempProg.getTrigger(i));
        if(tempProg.getTrigger(i) <= 1439)
        {
            if(first) first = false;
            else CMDprint(F(", "));
            byte minutes = tempProg.getTrigger(i)%60;
            CMDprint(String((tempProg.getTrigger(i)-minutes)/60));
            CMDprint(F(":"));
            CMDprint(String(minutes)+(minutes<10?F("0"):F("")));
        }
    }
    CMDprintln(F("}"));
    
    storeEEPROMData();
}

unsigned int ajustMaxuint(int number, unsigned int max)
{
  if(number >= max) return max;
  else return number;
}