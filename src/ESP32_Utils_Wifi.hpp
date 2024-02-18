
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ESPAsyncWebServer.h>

void ConnectWiFi_STA(bool useStaticIP = false)
{
    Serial.println("");
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID.c_str(), WIFI_KEY.c_str());
    if (useStaticIP)
        WiFi.config(WIFI_IP, WIFI_GATEWAY, WIFI_SUBNET, WIFI_DNS0, WIFI_DNS1);
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
    while (!WiFi.softAP(WIFI_SSID.c_str(), WIFI_KEY.c_str()))
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

void connectToWifi(bool ap_mode = true, bool useStaticIP = true)
{
    if (ap_mode)
        ConnectWiFi_AP(useStaticIP);
    else
        ConnectWiFi_STA(useStaticIP);
}

void InitWifi(bool ap_mode = WIFI_AP_MODE, bool useStaticIP = !WIFI_DHCP)
{
    connectToWifi(ap_mode, useStaticIP);
}