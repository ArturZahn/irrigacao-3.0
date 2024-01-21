#include "handlePrint.h"


unsigned int cmdBufferIndex = 0;
char cmdBuffer[cmdBufferSize+1];
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

void startCmdBuffering()
{
    clearCmdBuffer();
    LogBufferingState = true;
}
void stopCmdBuffering()
{
    clearCmdBuffer();
    LogBufferingState = false;
}
bool getCmdBufferingState()
{
    return LogBufferingState;
}


void cmdBufferPrint(String s)
{
    LOGprint(s);

    if(!LogBufferingState) return;

    for(char& c : s)
    {
        if(cmdBufferIndex < cmdBufferSize)
        {
            cmdBuffer[cmdBufferIndex] = c;
            cmdBufferIndex++;
        }
        // else bufferOverflowed = true;
    }
}

char* getCmdBuffer()
{
    // if(cmdState) return strcat("OK\n", cmdBuffer);
    // else return strcat("Erro\n", cmdBuffer);
    return cmdBuffer;
}

void clearCmdBuffer()
{
    memset(cmdBuffer, 0, sizeof(cmdBuffer));
    cmdBufferIndex = 0;
    cmdState = false;
    // bufferOverflowed = false;
}

// print without buffering
void LOGprint(String s)
{
    logBufferAdd(s);
    Serial.print(s);
}

void LOGprintln(String s)
{
    LOGprint(s);
    LOGprint("\n");
}


void LOGprint(char c)
{
    LOGprint(String(c));
}

void LOGprint(unsigned char b)
{
    LOGprint(String(b));
}

void LOGprint(int n)
{
    LOGprint(String(n));
}

void LOGprint(unsigned int n)
{
    LOGprint(String(n));
}

void LOGprint(long n)
{
    LOGprint(String(n));
}

void LOGprint(unsigned long n)
{
    LOGprint(String(n));
}

void LOGprint(double n)
{
    LOGprint(String(n));
}

void LOGprintln(void)
{
    LOGprintln("");
}

void LOGprintln(char c)
{
    LOGprintln(String(c));
}

void LOGprintln(unsigned char b)
{
    LOGprintln(String(b));
}

void LOGprintln(int num)
{
    LOGprintln(String(num));
}

void LOGprintln(unsigned int num)
{
    LOGprintln(String(num));
}

void LOGprintln(long num)
{
    LOGprintln(String(num));
}

void LOGprintln(unsigned long num)
{
    LOGprintln(String(num));
}

void LOGprintln(double num)
{
    LOGprintln(String(num));
}

// print CMD
void CMDprint(String s)
{
    cmdBufferPrint(s);
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

void CMDprint(double n)
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

void CMDprintln(double num)
{
    CMDprintln(String(num));
}

// CMDprint if log buffering is active, else LOGprint
void RPprint(String s)
{
    if(LogBufferingState) cmdBufferPrint(s);
    else LOGprint(s);
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

void RPprint(double n)
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

void RPprintln(double num)
{
    RPprintln(String(num));
}