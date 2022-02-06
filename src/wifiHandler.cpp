#include "wifiHandler.h"

WebServer mySasdasdafdfderver(80);
somethingHandler whenConnectionFinished;
bool connectedToWifi = false;
bool tringToConnect = false;
unsigned long wifiStartedConnect = 0;

void initWifi()
{
    WiFi.mode(WIFI_STA);
    connectWifi();
}

unsigned long lastVerify = 0;
void handleWifi()
{
    // handdle wifi status changes
    if(millis() - lastVerify > checkWifiStatusTime)
    {
        int wifiStatus = WiFi.status();
        connectedToWifi = wifiStatus == WL_CONNECTED;

        if(tringToConnect)
        {
            if(connectedToWifi || millis() - wifiStartedConnect > wifiFailConnectTime)
            {
                tringToConnect = false;
                
                if(whenConnectionFinished)
                {
                    whenConnectionFinished(connectedToWifi);
                    whenConnectionFinished = nullptr;
                }
            }
        }

        lastVerify = millis();
    }
}

bool setWifiSsid(String ssid)
{
    // if(ssid == "") return false;
    if(ssid.length() > wifiMaxSsidLen) return false;
    
    strcpy(d.wifi.ssid, ssid.c_str());
    storeEEPROMData();

    return true;
}

bool setWifiPassword(String password)
{
    if(password == "") return false;
    if(password.length() > wifiMaxPasswordLen) return false;
    
    strcpy(d.wifi.password, password.c_str());
    storeEEPROMData();

    return true;
}

void connectWifi()
{
    connectWifi(nullptr);
}

void connectWifi(somethingHandler wCF)
{
    whenConnectionFinished = wCF;
    wifiStartedConnect = millis();
    tringToConnect = true;
    Serial.println("millis: "+String(millis()));
    Serial.println("status connc: "+String(WiFi.begin(d.wifi.ssid, d.wifi.password)));
}

void disconnectWifi()
{
    WiFi.disconnect();
}

void showIp()
{
    Serial.print("IP adress: ");
    Serial.println(WiFi.localIP());
}

void exeWifiCommand(String cmd)
{
    String args;
    getCmd(cmd, &cmd, &args);

    if (cmd == "ssid")
    {
        getCmd(args, &cmd, &args);
        if(cmd == "definir")
        {
            if(setWifiSsid(args)) Serial.println("definido");
            else Serial.println("Erro, nome da rede vazio ou muito longo");
        }
        else if(cmd == "")
        {
            Serial.print("ssid: \"");
            Serial.print(d.wifi.ssid);
            Serial.println("\"");
        }
        else
        {
            Serial.print("ação \"");
            Serial.print(cmd);
            Serial.println("\" não existe");
        }
    }
    else if (cmd == "senha")
    {
        getCmd(args, &cmd, &args);
        if(cmd == "definir")
        {
            if(setWifiPassword(args)) Serial.println("definido");
            else Serial.println("Erro, senha muito longa");
        }
        else if(cmd == "")
        {
            Serial.print("senha: \"");
            Serial.print(d.wifi.password);
            Serial.println("\"");
        }
        else
        {
            Serial.print("ação \"");
            Serial.print(cmd);
            Serial.println("\" não existe");
        }
    }
    else if (cmd == "conectar")
    {
        Serial.print("Conectando à rede ");
        Serial.print(d.wifi.ssid);
        Serial.println("...");
        connectWifi([](bool success) {
            if(success){
                Serial.println("Conectado");
                showIp();
            }
            else Serial.println("Falha ao conectar à rede");
        });
    }
    else if (cmd == "desconectar")
    {
        disconnectWifi();
        Serial.println("Desconectado");
    }
    else if (cmd == "status")
    {
        Serial.println("conectado: "+String(connectedToWifi));
        showIp();
    }
    else
    {
        Serial.print("opção \"");
        Serial.print(cmd);
        Serial.println("\" não existe");
    }
}