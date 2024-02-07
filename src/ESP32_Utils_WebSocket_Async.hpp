#include <ArduinoJson.h>
#include "WebSocketsProcessing.hpp"

void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
    switch (type)
    {
    case WS_EVT_CONNECT:
        Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
        break;
    case WS_EVT_DISCONNECT:
        Serial.printf("WebSocket client #%u disconnected\n", client->id());
        break;
    case WS_EVT_DATA:
        handleWebSocketMessage(arg, data, len, client);
        break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
        break;
    }
}

void InitWebSockets()
{
    ws.onEvent(onWsEvent);
    server.addHandler(&ws);
    Serial.println("WebSocket server started");
}

void notifyWs(String reg, String value)
{
    JsonDocument json;
    json[reg] = value;
    json["time"] = getTime();
    char data[250];
    size_t len = serializeJson(json, data);
    ws.textAll(data, len);
}
void notifyWs(String reg, float value)
{
    JsonDocument json;
    json[reg] = value;
    json["time"] = getTime();
    char data[250];
    size_t len = serializeJson(json, data);
    ws.textAll(data, len);
}
void notifyWs(String reg, bool value)
{
    JsonDocument json;
    json[reg] = value;
    json["time"] = getTime();
    char data[250];
    size_t len = serializeJson(json, data);
    ws.textAll(data, len);
}