
void ConnectWiFi_STA(bool useStaticIP = false)
{
    Serial.println("");
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID.c_str(), WIFI_PASSWORD.c_str());
    if (useStaticIP)
        WiFi.config(WIFI_IP, WIFI_GATEWAY, WIFI_SUBNET);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(100);
        Serial.print('.');
    }

    Serial.println("");
    Serial.print("Iniciado STA:\t");
    Serial.println(WIFI_SSID);
    Serial.print("IP address:\t");
    Serial.println(WiFi.localIP());
}

void ConnectWiFi_AP(bool useStaticIP = false)
{
    Serial.println("");
    WiFi.mode(WIFI_AP);
    while (!WiFi.softAP(WIFI_SSID.c_str(), WIFI_PASSWORD.c_str()))
    {
        Serial.println(".");
        delay(100);
    }
    if (useStaticIP)
        WiFi.softAPConfig(WIFI_IP, WIFI_GATEWAY, WIFI_SUBNET);

    Serial.println("");
    Serial.print("Iniciado AP:\t");
    Serial.println(WIFI_SSID);
    Serial.print("IP address:\t");
    Serial.println(WiFi.softAPIP());
}

void connectToWifi(bool useStaticIP = false)
{
    if (WIFI_AP_MODE)
        ConnectWiFi_AP(useStaticIP);
    else
        ConnectWiFi_STA(useStaticIP);
}

void InitWifi(bool useStaticIP = false)
{
    connectToWifi();
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

void InitTime()
{
    configTime(0, 0, NTP_SERVER.c_str());
}