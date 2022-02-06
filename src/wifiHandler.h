#ifndef WIFIHANDLER_H
#define WIFIHANDLER_H

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "defaultCredentials.h"
#include "protectedData.h"
#include "aditionalFunctions.h"

#define wifiFailConnectTime 11000
#define checkWifiStatusTime 100

typedef std::function<void(bool)> somethingHandler;

void initWifi();
void initWebServer();
void handleWifi();
bool setWifiSsid(String ssid);
bool setWifiPassword(String password);
void connectWifi();
void connectWifi(somethingHandler connectionFinishedHandler);
void disconnectWifi();
void showIp();
void exeWifiCommand(String args);

#endif