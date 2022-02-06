#include "wifiHandler.h"

WebServer server(80);
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

void initWebServer()
{
  if (MDNS.begin("esp32")) NBprintln("MDNS responder started");
  else NBprintln("MDNS failed to start");

  
  server.on("/", []() {
    server.send(200, "text/plain", "root");
  });
  server.on("/favicon.ico", []() {
    server.send(200, "text/plain", "hmm favicon");
  });

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound([]() {
    server.send(200, "text/plain", "not found");
  });

  server.begin();
  NBprintln("HTTP server started");
}

unsigned long lastVerify = 0;
void handleWifi()
{
    server.handleClient();
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
    RPprint("IP adress: ");
    RPprintln((String)WiFi.localIP().toString());
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
            if(setWifiSsid(args)) CMDprintln("definido");
            else CMDprintln("Erro, nome da rede vazio ou muito longo");
        }
        else if(cmd == "")
        {
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
            if(setWifiPassword(args)) CMDprintln("definido");
            else CMDprintln("Erro, senha muito longa");
        }
        else if(cmd == "")
        {
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
        disconnectWifi();
        CMDprintln("Desconectado");
    }
    else if (cmd == "status")
    {
        CMDprintln("conectado: "+String(connectedToWifi));
        showIp();
    }
    else if (cmd == "web")
    {
        initWebServer();
    }
    else if (cmd == "s")
    {
        RPprint("wifi status: ");
        RPprintln(WiFi.status());
    }
    else
    {
        CMDprint("opção \"");
        CMDprint(cmd);
        CMDprintln("\" não existe");
    }
}