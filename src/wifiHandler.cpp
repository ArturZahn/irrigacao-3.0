#include "wifiHandler.h"

somethingHandler whenConnectionFinished;
bool connectedToWifi = false;
bool tringToConnect = false;
unsigned long wifiStartedConnect = 0;

void initWifi()
{
    WiFi.mode(WIFI_STA);

    initWebServer();
    
    CMDprint("Conectando à rede \"");
    CMDprint(d.wifi.ssid);
    CMDprintln("\"...");
    connectWifi([](bool success) {
        if(success){
            CMDprintln("Conectado");
            showIp();
        }
        else CMDprintln("Falha ao conectar à rede");
    });
}

unsigned long lastVerify = 0;
void handleWifi()
{
    handleWebServer();

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
    WiFi.begin(d.wifi.ssid, d.wifi.password);
    whenConnectionFinished = wCF;
    wifiStartedConnect = millis();
    tringToConnect = true;
}

void disconnectWifi()
{
    WiFi.disconnect();
}

void showIp()
{
    RPprint("Enderço IP: ");
    RPprintln((String)WiFi.localIP().toString());
}

void listNetworks() {
  // scan for nearby networks:
  int numSsid = WiFi.scanNetworks();
  if (numSsid == -1) {
    CMDprintln("Não há nenhuma rede disponível");
    return;
  }

  // print the list of networks seen:
  CMDprint("Redes disponíveis (");
  CMDprint(numSsid);
  CMDprintln("):");

  // print the network number and name for each network found:
  for (int thisNet = 0; thisNet < numSsid; thisNet++) {
    CMDprint(thisNet+1);
    CMDprint(") \"");
    CMDprint(WiFi.SSID(thisNet));
    CMDprint("\" ");
    CMDprint(WiFi.RSSI(thisNet));
    CMDprintln(" dBm");
  }
}

void exeWifiCommand(String cmd)
{
    String args;
    splitCmdArgs(cmd, &cmd, &args);

    if (cmd == "ssid")
    {
        splitCmdArgs(args, &cmd, &args);
        if(cmd == "definir")
        {
            if(setWifiSsid(args))
            {
                CMDprintln("definido");
                setCmdState(true);
            }
            else CMDprintln("Erro, nome da rede vazio ou muito longo");
        }
        else if(cmd == "")
        {
            setCmdState(true);
            CMDprint("ssid: \"");
            CMDprint(d.wifi.ssid);
            CMDprintln("\"");
        }
        else
        {
            CMDprint("ação \"");
            CMDprint(cmd);
            CMDprintln("\" não existe");
        }
    }
    else if (cmd == "senha")
    {
        splitCmdArgs(args, &cmd, &args);
        if(cmd == "definir")
        {
            if(setWifiPassword(args))
            {
                setCmdState(true);
                CMDprintln("definido");
            }
            else CMDprintln("Erro, senha muito longa");
        }
        else if(cmd == "")
        {
            setCmdState(true);
            CMDprint("senha: \"");
            CMDprint(d.wifi.password);
            CMDprintln("\"");
        }
        else
        {
            CMDprint("ação \"");
            CMDprint(cmd);
            CMDprintln("\" não existe");
        }
    }
    else if (cmd == "conectar")
    {
        setCmdState(true);
        CMDprint("Conectando à rede \"");
        CMDprint(d.wifi.ssid);
        CMDprintln("\"...");
        connectWifi([](bool success) {
            if(success){
                CMDprintln("Conectado");
                showIp();
            }
            else CMDprintln("Falha ao conectar à rede");
        });
    }
    else if (cmd == "desconectar")
    {
        setCmdState(true);
        disconnectWifi();
        CMDprintln("Desconectado");
    }
    else if (cmd == "status")
    {
        setCmdState(true);
        if(WiFi.status() != WL_CONNECTED)
        {
            CMDprintln("Desconectado");
            return;
        }
        
        CMDprint("Conectado em \"");
        CMDprint(WiFi.SSID());
        CMDprint("\" (");
        CMDprint(WiFi.RSSI());
        CMDprintln(" dBm)");
        showIp();
    }
    // wifi status
    else if (cmd == "listar")
    {
        setCmdState(true);
        listNetworks();
    }
    else
    {
        CMDprint("opção \"");
        CMDprint(cmd);
        CMDprintln("\" não existe");
    }
}