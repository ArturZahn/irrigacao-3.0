#include "wifiControlPanel.h"

WebServer server(80);

void initWebServer()
{
    if (MDNS.begin("esp32")) NBprintln("MDNS responder started");
    else NBprintln("MDNS failed to start");

    server.enableCORS(true);
    // server.enableCrossOrigin(true);
    
    server.onNotFound(handleNotFound);
    server.on("/", handleRoot);
    server.on("/needToUpdate", handleNeedToUpdate);


    server.begin();
    NBprintln("HTTP server started");
}

void handleWebServer()
{
    server.handleClient();
}

void handleNotFound() {

    if(server.uri().indexOf("/cli/") == 0)
    {
        handleCli(urlDecode(server.uri().substring(5)));
        return;
    }

    String message = "File Not Found\n\n";
    message += "URI: ";
    message += server.uri();
    message += "\nMethod: ";
    message += (server.method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server.args();
    message += "\n";
    for (uint8_t i = 0; i < server.args(); i++) {
        message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }
    server.send(404, "text/plain", message);
}

void handleRoot() {
  server.send(200, "text/html", "<!DOCTYPE html><html lang=\"pt-br\"><head></head><body><script>var espAddress = \""+((String)WiFi.localIP().toString())+"\";</script><script src=\"http://192.168.0.101:5500/html_ctrl_panel/loader.js\"></script></body></html>");
}

unsigned int updateNumber = 0;
void handleCli(String fullCmd)
{
    startLogBuffering();
    cliRunCommand(fullCmd);
    int state;
    if(getCmdState()) state = 200;
    else state = 400;
    server.send(state, "text/plain", getLogBuffer());
    stopLogBuffering();
}

void setNeedToUpdate()
{
    updateNumber++;
}

void handleNeedToUpdate()
{
    server.send(200, "text/plain", (String) updateNumber);
}