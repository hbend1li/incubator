#include "time.h"

void InitTime()
{
    configTime(0, 0, NTP_SERVER.c_str());
    Serial.print("Connected to NTP: ");
    Serial.println(NTP_SERVER);
}

unsigned long getTime()
{
    time_t now;
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        Serial.println("Failed to obtain time");
        return (0);
    }
    time(&now);
    return now;
}
