#ifndef WIFIHANDLER_H
#define WIFIHANDLER_H

#include <WiFi.h>
#include "protectedData.h"
#include "aditionalFunctions.h"
#include "wifiControlPanel.h"


#define nameHost "irrigacao"

#define wifiFailConnectTime 11000
#define checkWifiStatusTime 100

#define timeWithoutWifiBeforeTringToReconnect 60000
#define timeBetweenReconnectAttempts 20000

typedef std::function<void(bool)> somethingHandler;

void initWifi();
void initMDNS();
void handleWifi();
void handleReconnectToWifi(unsigned long nowMillis);
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