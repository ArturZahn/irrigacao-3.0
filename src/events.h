#ifndef EVENTS_H
#define EVENTS_H

#include "time.h"
#include <Arduino.h>


struct eventRawData {
    unsigned int sectors[4];
} // arrumar essa struct

// class event
// {
//     public:
    
// }

void checkEvents();

#endif