#ifndef REMOTESERIAL_H
#define REMOTESERIAL_H

#include <Arduino.h>

#define logBufferSize 512
#define logBufferTruncationIndecitionCharacter '\a'
void clearLogBuffer();
void printLogBuffer();
void flattenLogBuffer();
bool logBufferAvailable();
char logBufferGetChar();
void logBufferAdd(String);
String getLogBufferStr();
void initializeRemoteSerial();

#endif