#pragma once

AsyncMqttClient mqttClient;

// String GetPayloadContent(char *data, size_t len)
// {
//     String content = "";
//     for (size_t i = 0; i < len; i++)
//     {
//         content.concat(data[i]);
//     }
//     return content;
// }

// void SuscribeMqtt()
// {
//     uint16_t packetIdSub = mqttClient.subscribe("Ng3cKKI95qx3QI5pFTo2fCHK/r4", 0);
//     Serial.print("Subscribing at QoS 2, packetId: ");
//     Serial.println(packetIdSub);
// }

// void PublishMqtt()
// {
//     String payload = "";

//     JsonDocument jsonDoc;
//     jsonDoc["data"] = millis();
//     serializeJson(jsonDoc, payload);

//     mqttClient.publish("Ng3cKKI95qx3QI5pFTo2fCHK/r4", 0, true, (char *)payload.c_str());
// }

// void OnMqttReceived(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total)
// {
//     Serial.print("Received on ");
//     Serial.print(topic);
//     Serial.print(": ");

//     String content = GetPayloadContent(payload, len);

//     JsonDocument doc;
//     DeserializationError error = deserializeJson(doc, content);
//     if (error)
//         return;

//     unsigned long data = doc["data"];
//     Serial.print("Millis:");
//     Serial.println(data);
// }

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

// void updateGPIO(String input, bool value)
// {
//     String payload;
//     JsonDocument doc;
//     doc["command"] = "updateGPIO";
//     doc["id"] = input;
//     doc["status"] = value;
//     serializeJson(doc, payload);

//     mqttClient.publish("Ng3cKKI95qx3QI5pFTo2fCHK/r4", 0, true, (char *)payload.c_str());

//     Serial.print(input);
//     Serial.println(value ? String(" ON") : String(" OFF"));
// }

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