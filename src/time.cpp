#include "time.h"

unsigned long temporaryVar_time = 1577836800;
unsigned long getTime()
{
    temporaryVar_time += 60;
    return temporaryVar_time;
}

int getDayTime()
{
    return (getTime()%86400)/60;
}