#include "remoteSerial.h"

char logBuffer[logBufferSize];
unsigned int logBufferStartIndex = 0;
unsigned int logBufferEndIndex = 0;
// logBufferEndIndex meaning:
// if less than logBufferSize  →  indicates end of logBuffer (as normal)
// if equals logBufferSize     →  means that logBuffer is full, but didn't lose any character
// if equals logBufferSize+1   →  means that logBuffer is full and lost at least one character

void clearLogBuffer()
{
    logBufferStartIndex = 0;
    logBufferEndIndex = 1;
}

void printLogBuffer()
{
    while(logBufferAvailable()) Serial.print(logBufferGetChar());
}

bool logBufferAvailable()
{
    return
        logBufferEndIndex == logBufferSize ||
        logBufferStartIndex != logBufferEndIndex;
}

char logBufferGetChar()
{
    if(logBufferEndIndex == (logBufferSize+1))
    {
        logBufferEndIndex = logBufferSize;
        return logBufferTruncationIndecitionCharacter;
    }

    char c = logBuffer[logBufferStartIndex];

    if(logBufferEndIndex == logBufferSize)
        logBufferEndIndex = logBufferStartIndex;

    logBufferStartIndex++;
    if(logBufferStartIndex >= logBufferSize) logBufferStartIndex = 0;

    return c;
}

void logBufferAdd(String s)
{
    for(char& c : s)
    {
        if(logBufferEndIndex >= logBufferSize)
        {
            logBufferEndIndex = logBufferSize+1;
            
            logBuffer[logBufferStartIndex] = c;
            
            logBufferStartIndex++;
            if(logBufferStartIndex >= logBufferSize)
                logBufferStartIndex = 0;
        }
        else
        {
            logBuffer[logBufferEndIndex] = c;
            logBufferEndIndex++;
            if(logBufferEndIndex >= logBufferSize)
                logBufferEndIndex = 0;

            if(logBufferEndIndex == logBufferStartIndex) logBufferEndIndex = logBufferSize;
        }
    }
}

String getLogBufferStr()
{
    String s;
    while (logBufferAvailable())
        s += logBufferGetChar();
    
    return s;
}

void initializeRemoteSerial()
{
    logBufferAdd((String) logBufferTruncationIndecitionCharacter);
}