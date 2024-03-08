#ifndef WIFICONTROL_H
#define WIFICONTROL_H

#include <WebServer.h>
#include <ESPmDNS.h>
#include "handlePrint.h"
#include "aditionalFunctions.h"
#include "cli.h"
#include "ota.h"
#include "remoteSerial.h"

#define serverBaseUrl "https://arturzahn.github.io/irrigacao-3.0"

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