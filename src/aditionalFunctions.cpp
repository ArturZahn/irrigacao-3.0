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

// String urlEncode(String str)
// {
    // String encodedString="";
    // char c;
    // char code0;
    // char code1;
    // char code2;
    // for (int i =0; i < str.length(); i++){
    //   c=str.charAt(i);
    //   if (c == ' '){
    //     encodedString+= '+';
    //   } else if (isalnum(c)){
    //     encodedString+=c;
    //   } else{
    //     code1=(c & 0xf)+'0';
    //     if ((c & 0xf) >9){
    //         code1=(c & 0xf) - 10 + 'A';
    //     }
    //     c=(c>>4)&0xf;
    //     code0=c+'0';
    //     if (c > 9){
    //         code0=c - 10 + 'A';
    //     }
    //     code2='\0';
    //     encodedString+='%';
    //     encodedString+=code0;
    //     encodedString+=code1;
    //     //encodedString+=code2;
    //   }
    //   yield();
    // }
    // return encodedString;
    
// }
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
    
//     String encodedString="";
//     char c;
//     char code0;
//     char code1;
//     for (int i =0; i < str.length(); i++){
//         c=str.charAt(i);
//       if (c == '+'){
//         encodedString+=' ';  
//       }else if (c == '%') {
//         i++;
//         code0=str.charAt(i);
//         i++;
//         code1=str.charAt(i);
//         c = (h2int(code0) << 4) | h2int(code1);
//         encodedString+=c;
//       } else{
        
//         encodedString+=c;  
//       }
      
//       yield();
//     }
    
//    return encodedString;
}