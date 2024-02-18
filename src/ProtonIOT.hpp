#include <Certificate.h>

bool httpsInProgress = false;

String API_Key = "hSkThh17igEG6PhGhqz1ThQ3AqlFEeaWjv7YeovuAQ8PAGUnkF40C4idbRMFxtx6JwiR7KOo3mgfFxiI";
String cloudServer = "https://iot.proton-electronics.net/api/v1/iot";

int CloudSend(String key, String value)
{
    int httpResponseCode;
    //WiFiClientSecure *client = new WiFiClientSecure;
    WiFiClientSecure client;

    // Check WiFi connection status
    if (WiFi.status() == WL_CONNECTED)
    {
        //client->setCACert(rootCACertificate);
        //client.setInsecure();

        HTTPClient https;

        Serial.print("Try to Connect to Cloud ... ");
        if (https.begin(cloudServer.c_str()))
        {
            Serial.println("[Connect]");

            https.addHeader("Content-Type", "application/json");
            https.addHeader("Authorization", API_Key);
            httpResponseCode = https.POST("{\"" + key + "\":\"" + value + "\"}");

            if (httpResponseCode != HTTP_CODE_OK)
            {
                Serial.print("HTTP Response code: ");
                Serial.println(httpResponseCode);
            }
            else
            {
                Serial.println("HTTP Response code HTTP_CODE_OK");
            }

            https.end();
        }else{
            Serial.println("[Field]");

        }
        httpsInProgress = false;
        //delay(1000);
    }
    return httpResponseCode;
}

void InitCloudIot()
{
    CloudSend("[Info]", "System restarted.");
}