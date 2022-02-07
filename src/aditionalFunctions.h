#ifndef ADITIONALFUNCTIONS_H
#define ADITIONALFUNCTIONS_H

#include <Arduino.h>
#include "handlePrint.h"

// #include <ESP8266WiFi.h>
// // #include <WiFiClient.h>
// // #include <ESP8266WebServer.h>

void restartSystem();
void splitCmdArgs(String cmdArgs, String *cmd, String *args);
// String urlEncode(String str);
String urlDecode(String str);

#endif