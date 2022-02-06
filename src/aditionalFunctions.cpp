#include "aditionalFunctions.h"

void restartSystem()
{
    NBprintln("Restart ESP...");
    ESP.restart();
}

void splitCmdArgs(String cmdArgs, String *cmd, String *args)
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