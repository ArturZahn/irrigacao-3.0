#ifndef HANDLEPRINT_H
#define HANDLEPRINT_H

#include <Arduino.h>

#define logBufferSize 512

void initPrint();
void setCmdState(bool s);
bool getCmdState();

void bufferPrint(String s);

void startLogBuffering();
void stopLogBuffering();
bool getLogBufferingState();
char* getLogBuffer();
void clearLogBuffer();

void NBprint(String s);
void NBprintln(String s);
void NBprint(char c);
void NBprint(unsigned char b);
void NBprint(int n);
void NBprint(unsigned int n);
void NBprint(long n);
void NBprint(unsigned long n);
void NBprintln(void);
void NBprintln(char c);
void NBprintln(unsigned char b);
void NBprintln(int num);
void NBprintln(unsigned int num);
void NBprintln(long num);
void NBprintln(unsigned long num);

void CMDprint(String s);
void CMDprintln(String s);
void CMDprint(char c);
void CMDprint(unsigned char b);
void CMDprint(int n);
void CMDprint(unsigned int n);
void CMDprint(long n);
void CMDprint(unsigned long n);
void CMDprintln(void);
void CMDprintln(char c);
void CMDprintln(unsigned char b);
void CMDprintln(int num);
void CMDprintln(unsigned int num);
void CMDprintln(long num);
void CMDprintln(unsigned long num);

void RPprint(String s);
void RPprintln(String s);
void RPprint(char c);
void RPprint(unsigned char b);
void RPprint(int n);
void RPprint(unsigned int n);
void RPprint(long n);
void RPprint(unsigned long n);
void RPprintln(void);
void RPprintln(char c);
void RPprintln(unsigned char b);
void RPprintln(int num);
void RPprintln(unsigned int num);
void RPprintln(long num);
void RPprintln(unsigned long num);

#endif