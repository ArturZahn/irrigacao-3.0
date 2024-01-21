#ifndef WIFICONTROL_H
#define WIFICONTROL_H

#include <WebServer.h>
#include <ESPmDNS.h>
#include "handlePrint.h"
#include "aditionalFunctions.h"
#include "cli.h"
#include "ota.h"
#include "remoteSerial.h"

// #define serverBaseUrl "http://192.168.1.5:5500"
#define serverBaseUrl "http://192.168.211.60:5500"

void initWebServer();
void restartServer();

WebServer* getWebServerInstance();

void handleWebServer();
void handleNotFound();
void handleRoot();
void handleCli(String fullCmd);
void setNeedToUpdate();
void handleNeedToUpdate();
void handleRemoteSerial();

#endif