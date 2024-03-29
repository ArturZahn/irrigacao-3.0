#include "watchSoil.h"

unsigned int nOfStoredMeasures;
measures_stc measures[numberOfMeasuresArray];
bool debugSensorStatus = false;

void initWatchSoil()
{
    pinMode(soilMoistureSensor, INPUT);

    nOfStoredMeasures = 0;
}

unsigned long lastSoilMeasure = 0;
void handleWatchSoil()
{
    if(millis() - lastSoilMeasure > timeBetweenSoilMeasures)
    {
        lastSoilMeasure = millis();

        startMeasuringSoil();
    }

    handleSoilMeasuring();
    handleDebugSensor();
}

int currentSpacedSubMeasure = 0;
unsigned long lastSpacedSubMeasure = 0;
unsigned long measuresSum = 0;
void startMeasuringSoil()
{
    if(currentSpacedSubMeasure != 0) return;
    // LOGprintln("Starting measure...");

    currentSpacedSubMeasure = 1;
    lastSpacedSubMeasure = millis() - delayBetweenSpacedSubMeasures - 100;
    measuresSum = 0;
}

void handleSoilMeasuring()
{
    // LOGprint("ctr: ");
    // LOGprintln(currentSpacedSubMeasure);
    if(currentSpacedSubMeasure == 0) return;

    if(millis() - lastSpacedSubMeasure > delayBetweenSpacedSubMeasures)
    {
        lastSpacedSubMeasure = millis();

        
        // LOGprint("making sub measure...");

        measuresSum += makeSubMeasure();
        currentSpacedSubMeasure++;
        if(currentSpacedSubMeasure > numberOfSpacedSubMeasures)
        {
            measuresSum /= numberOfSpacedSubMeasures;
            currentSpacedSubMeasure = 0;
            handleNewMeasure(measuresSum);
            measuresSum = 0;
        }
    }
}

#ifdef fakeSoilMoistureSensor
unsigned int tempAlalogReadSimulator = 0;
#endif
unsigned int makeSubMeasure()
{
    unsigned long tempMeasuresSum = 0;
    for(int i = 0; i < numberOfSubSubMeasures; i++)
    {
        #ifndef fakeSoilMoistureSensor
        tempMeasuresSum += analogRead(soilMoistureSensor);
        #else
        tempAlalogReadSimulator++;
        tempMeasuresSum += tempAlalogReadSimulator;
        #endif
    }

    // LOGprint(" > ");
    // LOGprintln(tempMeasuresSum/numberOfSubSubMeasures);

    return tempMeasuresSum/numberOfSubSubMeasures;
}

void handleNewMeasure(unsigned int newMeasure)
{
    if(nOfStoredMeasures >= numberOfMeasuresArray)
    {
        // if buffer is full, remove oldest measure

        // LOGprintln("Buffer cheio");
        for (int i = 1; i < numberOfMeasuresArray; i++)
        {
            measures[i-1].time = measures[i].time;
            measures[i-1].value = measures[i].value;
        }
        nOfStoredMeasures--;
    }
    
    // LOGprintln("adicionando ao buffer\n");
    measures[nOfStoredMeasures].value = newMeasure;
    measures[nOfStoredMeasures].time = getTime();
    nOfStoredMeasures++;

    // showSoilMeasurings();
}

unsigned int showSoilMeasuringsLimited(unsigned int qtd)
{
    if(qtd == 0 || qtd > maxNumberOfMeasuresLimited) qtd = maxNumberOfMeasuresLimited;

    qtd = showSoilMeasurings(qtd);
    return qtd;
}

unsigned int showSoilMeasurings(unsigned int qtd)
{
    if(qtd == 0 || qtd > nOfStoredMeasures) qtd = nOfStoredMeasures;

    CMDprint("Medidas (");
    CMDprint(qtd);
    CMDprint("/");
    CMDprint(nOfStoredMeasures);
    CMDprintln("):");
    for (int i = 0; i < qtd; i++)
    {
        CMDprint(measures[i].time);
        CMDprint(">");
        CMDprintln(measures[i].value);
    }
    CMDprintln("\n");

    return qtd;
}

void showSoilMeasurings()
{
    showSoilMeasurings(0);
}

void clearSoilMeasurings(unsigned int qtd)
{
    if(qtd == 0 || qtd >= nOfStoredMeasures)
    {
        clearSoilMeasurings();
        return;
    }

    for (int i = 0; i < numberOfMeasuresArray-qtd; i++)
    {
        measures[i] = measures[i+qtd];
    }
    nOfStoredMeasures -= qtd;
}

void clearSoilMeasurings()
{
    nOfStoredMeasures = 0;
}

void showAndClearSoilMeasurings()
{
    unsigned int qtd = showSoilMeasuringsLimited(0);
    clearSoilMeasurings(qtd);
}

void setDebugSensor(bool stt)
{
    debugSensorStatus = stt;
}

void handleDebugSensor()
{
    if(!debugSensorStatus) return;

    LOGprintln(makeSubMeasure());
}