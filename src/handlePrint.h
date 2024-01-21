#ifndef HANDLEPRINT_H
#define HANDLEPRINT_H

#include <Arduino.h>

void initPrint();
void setCmdState(bool s);
bool getCmdState();

#define cmdBufferSize 512
void cmdBufferPrint(String s);
void startCmdBuffering();
void stopCmdBuffering();
bool getCmdBufferingState();
char* getCmdBuffer();
void clearCmdBuffer();

void LOGprint(String s);
void LOGprintln(String s);
void LOGprint(char c);
void LOGprint(unsigned char b);
void LOGprint(int n);
void LOGprint(unsigned int n);
void LOGprint(long n);
void LOGprint(unsigned long n);
void LOGprint(double n);
void LOGprintln(void);
void LOGprintln(char c);
void LOGprintln(unsigned char b);
void LOGprintln(int num);
void LOGprintln(unsigned int num);
void LOGprintln(long num);
void LOGprintln(unsigned long num);
void LOGprintln(double num);

void CMDprint(String s);
void CMDprintln(String s);
void CMDprint(char c);
void CMDprint(unsigned char b);
void CMDprint(int n);
void CMDprint(unsigned int n);
void CMDprint(long n);
void CMDprint(unsigned long n);
void CMDprint(double n);
void CMDprintln(void);
void CMDprintln(char c);
void CMDprintln(unsigned char b);
void CMDprintln(int num);
void CMDprintln(unsigned int num);
void CMDprintln(long num);
void CMDprintln(unsigned long num);
void CMDprintln(double num);

void RPprint(String s);
void RPprintln(String s);
void RPprint(char c);
void RPprint(unsigned char b);
void RPprint(int n);
void RPprint(unsigned int n);
void RPprint(long n);
void RPprint(unsigned long n);
void RPprint(double n);
void RPprintln(void);
void RPprintln(char c);
void RPprintln(unsigned char b);
void RPprintln(int num);
void RPprintln(unsigned int num);
void RPprintln(long num);
void RPprintln(unsigned long num);
void RPprintln(double num);

#endif