#include "aditionalFunctions.h"

void restartSystem()
{
    LOGprintln("Restart ESP...");
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

String urlDecode(String str)
{
    char data[str.length()+1];
    strcpy(data, str.c_str());

    // Create two pointers that point to the start of the data
    char *leader = data;
    char *follower = leader;

    // While we're not at the end of the string (current character not NULL)
    while (*leader) {
        // Check to see if the current character is a %
        if (*leader == '%') {

            // Grab the next two characters and move leader forwards
            leader++;
            char high = *leader;
            leader++;
            char low = *leader;

            // Convert ASCII 0-9A-F to a value 0-15
            if (high > 0x39) high -= 7;
            high &= 0x0f;

            // Same again for the low byte:
            if (low > 0x39) low -= 7;
            low &= 0x0f;

            // Combine the two into a single byte and store in follower:
            *follower = (high << 4) | low;
        } else {
            // All other characters copy verbatim
            *follower = *leader;
        }

        // Move both pointers to the next character:
        leader++;
        follower++;
    }
    // Terminate the new string with a NULL character to trim it off
    *follower = 0;

    return data;
}

bool isNumber(const String& str)
{
    if(str == "") return false;
    
    for (char const &c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}