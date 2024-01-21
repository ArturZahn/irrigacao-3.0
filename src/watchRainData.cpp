#include "watchRainData.h"

WiFiClient client_asdasdasd;

std::vector<rainData_t> rainData;

bool updateRainData()
{
    updateRainData(false);
}
bool debugRainData()
{
    LOGprintln("ASD 1");
    updateRainData(true);
}
bool updateRainData(bool printResponseInsteadOfFindingTheData)
{
    // client_asdasdasd.available();
    if(!isConnectedToWifi()) return false;

    #define TEST_HOST "www.ciiagro.org.br"
    if (!client_asdasdasd.connect(TEST_HOST, 80))
    {
        RPprintln(F("Could not update rain data, connection failed"));
        return false;
    }

    yield();

    // Send HTTP request
    client_asdasdasd.print(F("GET "));
    // This is the second half of a request (everything that comes after the base URL)
    client_asdasdasd.print("/ema/index.php?id=63"); // %2C == ,
    client_asdasdasd.println(F(" HTTP/1.1"));

    //Headers
    client_asdasdasd.print(F("Host: "));
    client_asdasdasd.println(TEST_HOST);

    client_asdasdasd.println(F("Cache-Control: no-cache"));

    // need to add this header, it does not make sense but without it ciiagro.com send the data for the wrong city
    // the city selected below does not matter, just the one in the request.
    client_asdasdasd.println(F("Referer: http://www.ciiagro.org.br/ema/index.php?id=63"));

    if (client_asdasdasd.println() == 0)
    {
        RPprintln(F("Could not update rain data, failed to send request"));
        return false;
    }
    //delay(100);
    // Check HTTP status
    char status[32] = {0};
    client_asdasdasd.readBytesUntil('\r', status, sizeof(status));
    if (strcmp(status, "HTTP/1.1 200 OK") != 0)
    {
        RPprint(F("Could not update rain data, unexpected response: "));
        RPprintln(status);
        return false;
    }

    // Skip HTTP headers
    char endOfHeaders[] = "\r\n\r\n";
    if (!client_asdasdasd.find(endOfHeaders))
    {
        RPprintln(F("Could not update rain data, invalid response"));
        return false;
    }

    if(!printResponseInsteadOfFindingTheData) {
        if(!filterData())
        {
            RPprintln("Could not update rain data, could not filter data");
            return false;
        }
    }
    else
    {
        LOGprintln("Response:");
        while (client_asdasdasd.available()) {
            char nextChar;
            client_asdasdasd.readBytes(&nextChar, 1);
            LOGprint(nextChar);
        }
        LOGprintln("ended");
        client_asdasdasd.stop();
        return false;
    }

    client_asdasdasd.stop();
    return true;
}


unsigned long lastSucessfulRainDataRequest = -timeBetweenSucessfulRainDataRequest;
unsigned long lastRainDataRequestAttempt = -timeBetweenRainDataRequestAttemps;
void handleWatchRainData()
{
    if(!(millis() - lastSucessfulRainDataRequest > timeBetweenSucessfulRainDataRequest))
        return;

    if(!(millis() - lastRainDataRequestAttempt > timeBetweenRainDataRequestAttemps))
        return;
        
    // LOGprintln("PRE");
    // LOGprint(getStrDateTime());
    // LOGprint("Asdasd");
    LOGprintln(" Get rain attempt");
    
    lastRainDataRequestAttempt = millis();
    
    // if(updateRainData())
    if(debugRainData())
    {
        lastSucessfulRainDataRequest = lastRainDataRequestAttempt;
        LOGprintln("Get rain successful");
    }
}

bool filterData()
{
    if (!readResponseUntil(F("<caption>Dados meteorológicos das últimas 12 horas</caption>")))
    {
        LOGprintln("FAIL 1");
        return false;
    }

    if (!readResponseUntil("<tbody>"))
    {
        LOGprintln("FAIL 2");
        return false;
    }

    String data;
    if (!readResponseUntilAndSaveToString("</tbody>", &data))
    {
        LOGprintln("FAIL 3");
        return false;
    }

    while(data.indexOf("\r") != -1) data.replace("\r", "");
    while(data.indexOf("\n") != -1) data.replace("\n", "");
    while(data.indexOf(" <") != -1) data.replace(" <", "<");
    while(data.indexOf("</tbody>") != -1) data.replace("</tbody>", "");
    
    unsigned int temp0, temp1, temp2;
    temp0 = 0;
    while(data.indexOf("<tr><td>", temp0) != -1)
    {    
        temp1 = data.indexOf("<tr><td>", temp0)+8;
        temp2 = data.indexOf("</td>", temp1);
        String time = data.substring(temp1, temp2);
        
        for(int i = 0; i < 3; i++){
            temp1 = temp2+9;
            temp2 = data.indexOf("</td>", temp1);
        }
        temp0 = temp2;

        String rain = data.substring(temp1, temp2);


        byte second, minute, hour, day, month; int year;

        time = time.substring(11) + ":00 "+time.substring(0, 10);

        if(parseTime(time, second, minute, hour, day, month, year))
        {
            DateTime dt(year, month, day, hour, minute, second);
            unsigned int dt_unix = dt.unixtime();

            rainData_t newRain;
            newRain.unixtime = dt_unix;
            rain.replace(",", ".");
            newRain.rain = rain.toDouble();

            // check if reading already is in vector rainData
            auto it = std::find_if(rainData.begin(), rainData.end(),
                [dt_unix](const rainData_t& element) {
                    LOGprintln("FAIL 4");
                    return element.unixtime == dt_unix;
                }
            );
            if (it == rainData.end()) // if not found
            {
                rainData.push_back(newRain);
            }
        }
    }
    
    return true;
}

bool readResponseUntilAndSaveToString(String searchString, String* savedString)
{
    bool foundString = false;

    if(savedString != nullptr) *savedString = "";

    if(!client_asdasdasd.available())
    {
        LOGprintln("not available 1");
        return false;
    }

    do {
        int i = 0;
       
        while (i < searchString.length() && client_asdasdasd.available()) {
            char nextChar;
            client_asdasdasd.readBytes(&nextChar, 1);
            if(savedString != nullptr) *savedString += nextChar;

            LOGprint(nextChar);

            if (nextChar == searchString[i]) i++;
            else i = 0;
        }
        
        if (i == searchString.length()) {
            foundString = true;
            break;
        }
    }
    while (client_asdasdasd.available());

    if(!foundString)
    {
        LOGprintln("string not found");
    }

    return foundString;
}

bool readResponseUntil(String searchString)
{
    return readResponseUntilAndSaveToString(searchString, nullptr);
}

void clearRainData()
{
    rainData.clear();
}

void printRainData()
{
    RPprintln("Rain data: ");
    for (int i = 0; i < rainData.size(); i++)
    {
        RPprint(rainData[i].unixtime);
        RPprint(" - ");
        RPprintln(rainData[i].rain);
    }
    
    RPprint("\nTotal rain: ");
    RPprintln(sumRainFromData());
}

void filterOutOldData()
{
    for (int i = 0; i < rainData.size(); i++)
    {
        double dataAge = ((double)(getTime()-rainData[i].unixtime))/3600;
        if(dataAge > maxRainDataAge)
        {
            rainData.erase(rainData.begin() + i);
            i--;
        }
    }
}

unsigned int sumRainFromData()
{
    unsigned int sum = 0;

    for (int i = 0; i < rainData.size(); i++)
    {
        sum += rainData[i].rain;
    }
    
    return sum;
}

bool isAlreadyMoist()
{
    filterOutOldData();
    return sumRainFromData() >= milimetersOfRainToConsiderMoist;
}