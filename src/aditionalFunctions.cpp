#include "aditionalFunctions.h"

void restartSystem()
{
    Serial.println("Restart ESP...");
    ESP.restart();
}

void getCmd(String cmdArgs, String *cmd, String *args)
{
    int idxOfThing = cmdArgs.indexOf(" ");
    if(idxOfThing == -1)
    {
        (*cmd) = cmdArgs;
        (*args) = "";
    }
    else
    {
        (*cmd) = cmdArgs.substring(0, idxOfThing);
        (*args) = cmdArgs.substring(idxOfThing+1);
    }
}