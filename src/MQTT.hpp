#pragma once

#include <AsyncMqttClient.h>

AsyncMqttClient mqttClient;

String GetPayloadContent(char *data, size_t len)
{
    String content = "";
    for (size_t i = 0; i < len; i++)
    {
        content.concat(data[i]);
    }
    return content;
}

void SuscribeMqtt()
{
    mqttClient.subscribe(String(MQTT_SUB + "/r3").c_str(), 0);
    mqttClient.subscribe(String(MQTT_SUB + "/r4").c_str(), 0);
}

void OnMqttReceived(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total)
{
    Serial.print("Received on ");
    Serial.print(topic);
    Serial.println(": ");

    String content = GetPayloadContent(payload, len);

    if (String(topic) == (MQTT_SUB + "/r3"))
    {
        relay_3 = (content == "1") ? true : false;
    }

    if (String(topic) == (MQTT_SUB + "/r4"))
    {
        relay_4 = (content == "1") ? true : false;
    }
}