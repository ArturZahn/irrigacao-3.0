#include "handlePrint.h"

char logBuffer[logBufferSize+1];
unsigned int logBufferIndex = 0;
// bool bufferOverflowed = false;
bool LogBufferingState = false;
bool cmdState = false;

void initPrint()
{
    Serial.begin(115200);
}

void setCmdState(bool s)
{
    cmdState = s;
}
bool getCmdState()
{
    return cmdState;
}

void startLogBuffering()
{
    clearLogBuffer();
    LogBufferingState = true;
}
void stopLogBuffering()
{
    clearLogBuffer();
    LogBufferingState = false;
}
bool getLogBufferingState()
{
    return LogBufferingState;
}


void bufferPrint(String s)
{
    NBprint(s);

    if(!LogBufferingState) return;

    for(char& c : s) {
        if(logBufferIndex < logBufferSize)
        {
            logBuffer[logBufferIndex] = c;
            logBufferIndex++;
        }
        // else bufferOverflowed = true;
    }
}

char* getLogBuffer()
{
    // if(cmdState) return strcat("OK\n", logBuffer);
    // else return strcat("Erro\n", logBuffer);
    return logBuffer;
}

void clearLogBuffer()
{
    memset(logBuffer, 0, sizeof(logBuffer));
    logBufferIndex = 0;
    cmdState = false;
    // bufferOverflowed = false;
}

// print without buffering
void NBprint(String s)
{
    Serial.print(s);
}

void NBprintln(String s)
{
    NBprint(s);
    NBprint("\n");
}


void NBprint(char c)
{
    NBprint(String(c));
}

void NBprint(unsigned char b)
{
    NBprint(String(b));
}

void NBprint(int n)
{
    NBprint(String(n));
}

void NBprint(unsigned int n)
{
    NBprint(String(n));
}

void NBprint(long n)
{
    NBprint(String(n));
}

void NBprint(unsigned long n)
{
    NBprint(String(n));
}

void NBprintln(void)
{
    NBprintln("");
}

void NBprintln(char c)
{
    NBprintln(String(c));
}

void NBprintln(unsigned char b)
{
    NBprintln(String(b));
}

void NBprintln(int num)
{
    NBprintln(String(num));
}

void NBprintln(unsigned int num)
{
    NBprintln(String(num));
}

void NBprintln(long num)
{
    NBprintln(String(num));
}

void NBprintln(unsigned long num)
{
    NBprintln(String(num));
}

// print CMD
void CMDprint(String s)
{
    bufferPrint(s);
}

void CMDprintln(String s)
{
    CMDprint(s);
    CMDprint("\n");
}

void CMDprint(char c)
{
    CMDprint(String(c));
}

void CMDprint(unsigned char b)
{
    CMDprint(String(b));
}

void CMDprint(int n)
{
    CMDprint(String(n));
}

void CMDprint(unsigned int n)
{
    CMDprint(String(n));
}

void CMDprint(long n)
{
    CMDprint(String(n));
}

void CMDprint(unsigned long n)
{
    CMDprint(String(n));
}

void CMDprintln(void)
{
    CMDprintln("");
}

void CMDprintln(char c)
{
    CMDprintln(String(c));
}

void CMDprintln(unsigned char b)
{
    CMDprintln(String(b));
}

void CMDprintln(int num)
{
    CMDprintln(String(num));
}

void CMDprintln(unsigned int num)
{
    CMDprintln(String(num));
}

void CMDprintln(long num)
{
    CMDprintln(String(num));
}

void CMDprintln(unsigned long num)
{
    CMDprintln(String(num));
}

// CMDprint if log buffering is active, else NBprint
void RPprint(String s)
{
    if(LogBufferingState) bufferPrint(s);
    else NBprint(s);
}

void RPprintln(String s)
{
    RPprint(s);
    RPprint("\n");
}

void RPprint(char c)
{
    RPprint(String(c));
}

void RPprint(unsigned char b)
{
    RPprint(String(b));
}

void RPprint(int n)
{
    RPprint(String(n));
}

void RPprint(unsigned int n)
{
    RPprint(String(n));
}

void RPprint(long n)
{
    RPprint(String(n));
}

void RPprint(unsigned long n)
{
    RPprint(String(n));
}

void RPprintln(void)
{
    RPprintln("");
}

void RPprintln(char c)
{
    RPprintln(String(c));
}

void RPprintln(unsigned char b)
{
    RPprintln(String(b));
}

void RPprintln(int num)
{
    RPprintln(String(num));
}

void RPprintln(unsigned int num)
{
    RPprintln(String(num));
}

void RPprintln(long num)
{
    RPprintln(String(num));
}

void RPprintln(unsigned long num)
{
    RPprintln(String(num));
}