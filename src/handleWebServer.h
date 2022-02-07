#ifndef HANDLEWEBSERVER_H
#define HANDLEWEBSERVER_H

#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "handlePrint.h"
#include "aditionalFunctions.h"
#include "cli.h"

void initWebServer();
void handleWebServer();
void handleNotFound();
void handleRoot();
void handleCli(String fullCmd);

#endif