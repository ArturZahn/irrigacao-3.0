#include "handleWebServer.h"

WebServer server(80);

void initWebServer()
{
    if (MDNS.begin("esp32")) NBprintln("MDNS responder started");
    else NBprintln("MDNS failed to start");

    server.enableCORS(true);
    // server.enableCrossOrigin(true);
    
    server.onNotFound(handleNotFound);
    server.on("/", handleRoot);


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
        NBprintln("entrou");
        handleCli(urlDecode(server.uri().substring(5)));
        return;
    }
    NBprintln("nao entrou");

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
  server.send(200, "text/plain", "root");
}

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

