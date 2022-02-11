#ifndef WIFIHANDLER_H
#define WIFIHANDLER_H

#include <WiFi.h>
#include "protectedData.h"
#include "aditionalFunctions.h"
#include "wifiControlPanel.h"

#define wifiFailConnectTime 11000
#define checkWifiStatusTime 100

typedef std::function<void(bool)> somethingHandler;

void initWifi();
void handleWifi();
bool setWifiSsid(String ssid);
bool setWifiPassword(String password);
void connectWifi();
void connectWifi(somethingHandler connectionFinishedHandler);
bool isConnectedToWifi();
void disconnectWifi();
void showIp();
void listNetworks();
void exeWifiCommand(String args);

#endif