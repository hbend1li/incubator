#include <ArduinoJson.h>
AsyncWebSocket ws("/ws");

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len, AsyncWebSocketClient *client)
{
    AwsFrameInfo *info = (AwsFrameInfo *)arg;
    if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT)
    {
        JsonDocument doc, json;
        DeserializationError err = deserializeJson(doc, data);
        if (err)
        {
            Serial.print(F("deserializeJson() failed with code "));
            Serial.println(err.c_str());
            return;
        }

        String command = doc["cmd"];

        if (command == "setRelay")
        {
            bool r1 = doc["r1"];
            bool r2 = doc["r2"];
            bool r3 = doc["r3"];
            bool r4 = doc["r4"];
            relay_1 = r1;
            relay_2 = r2;
            relay_3 = r3;
            relay_4 = r4;
        }
        else if (command == "setWifi")
        {
            String wifi_ssid = doc["wifi_ssid"];
            String wifi_password = doc["wifi_password"];
            String wifi_hostname = doc["wifi_hostname"];
            String wifi_ap_mode = doc["wifi_ap_mode"];
            String wifi_dhcp = doc["wifi_dhcp"];
            String wifi_ip = doc["wifi_ip"];
            String wifi_subnet = doc["wifi_subnet"];
            String wifi_gateway = doc["wifi_gateway"];
            String wifi_dns0 = doc["wifi_dns0"];
            String wifi_dns1 = doc["wifi_dns1"];

            WIFI_SSID = wifi_ssid;
            WIFI_PASSWORD = wifi_password;
            WIFI_HOSTNAME = wifi_hostname;
            WIFI_AP_MODE = wifi_ap_mode;
            WIFI_DHCP = wifi_dhcp;
            WIFI_IP.fromString(wifi_ip);
            WIFI_SUBNET.fromString(wifi_subnet);
            WIFI_GATEWAY.fromString(wifi_gateway);
            WIFI_DNS0.fromString(wifi_dns0);
            WIFI_DNS1.fromString(wifi_dns1);

            preferences.putString("wifi_ssid", WIFI_SSID);
            preferences.putString("wifi_password", WIFI_PASSWORD);
            preferences.putString("wifi_hostname", WIFI_HOSTNAME);
            preferences.putBool("wifi_ap_mode", WIFI_AP_MODE);
            preferences.putBool("wifi_dhcp", WIFI_DHCP);
            preferences.putString("wifi_ip", wifi_ip);
            preferences.putString("wifi_subnet", wifi_subnet);
            preferences.putString("wifi_gateway", wifi_gateway);
            preferences.putString("wifi_dns0", wifi_dns0);
            preferences.putString("wifi_dns1", wifi_dns1);
        }
        else if (command == "setMqtt")
        {
            String mqtt_host = json["mqtt_host"];
            uint16_t mqtt_port = json["mqtt_port"];
            String mqtt_username = json["mqtt_username"];
            String mqtt_password = json["mqtt_password"];
            String mqtt_sub = json["mqtt_sub"];

            MQTT_HOST = mqtt_host;
            MQTT_PORT = mqtt_port;
            MQTT_USERNAME = mqtt_username;
            MQTT_PASSWORD = mqtt_password;
            MQTT_SUB = mqtt_sub;

            preferences.putString("mqtt_host", MQTT_HOST);
            preferences.putShort("mqtt_port", MQTT_PORT);
            preferences.putString("mqtt_username", MQTT_USERNAME);
            preferences.putString("mqtt_password", MQTT_PASSWORD);
            preferences.putString("mqtt_sub", MQTT_SUB);
        }
        else if (command == "setParam")
        {
            temperature_min = json["tL"];
            temperature_max = json["tH"];
            humidity_min = json["hL"];
            humidity_max = json["hH"];
            preferences.putFloat("t_min", temperature_min);
            preferences.putFloat("t_max", temperature_max);
            preferences.putFloat("h_min", humidity_min);
            preferences.putFloat("h_max", humidity_max);
        }
        else if (command == "delete")
        {
            File file = SPIFFS.open("/data.csv", FILE_WRITE);
            file.print("");
            file.close();
        }

        if (command == "getTemperature")
        {
            json["Temperature"] = Temperature;
        }
        else if (command == "getHumidity")
        {
            json["Humidity"] = Humidity;
        }
        else if (command == "getStatus")
        {
            json["Temperature"] = Temperature;
            json["Humidity"] = Humidity;
            json["r1"] = relay_1;
            json["r2"] = relay_2;
            json["r3"] = relay_3;
            json["r4"] = relay_4;
        }
        else if (command == "getParam" || command == "setParam")
        {
            json["tL"] = temperature_min;
            json["tH"] = temperature_max;
            json["hL"] = humidity_min;
            json["hH"] = humidity_max;
        }
        else if (command == "getWifi" || command == "setWifi")
        {
            json["wifi_ssid"] = WIFI_SSID;
            json["wifi_key"] = WIFI_PASSWORD;
            json["wifi_ap_mode"] = WIFI_AP_MODE;
            json["wifi_dhcp"] = WIFI_DHCP;
            json["wifi_ip"] = WIFI_IP;
            json["wifi_subnet"] = WIFI_SUBNET;
            json["wifi_gateway"] = WIFI_GATEWAY;
            json["wifi_dns0"] = WIFI_DNS0;
            json["wifi_dns1"] = WIFI_DNS1;
        }
        else if (command == "getMqtt" || command == "setMqtt")
        {
            json["mqtt_host"] = MQTT_HOST;
            json["mqtt_port"] = MQTT_PORT;
            json["mqtt_username"] = MQTT_USERNAME;
            json["mqtt_password"] = MQTT_PASSWORD;
            json["mqtt_sub"] = MQTT_SUB;
        }
        else if (command == "getSpiffs" || command == "delete")
        {
            json["spiffs_u"] = String(SPIFFS.usedBytes());
            json["spiffs_t"] = String(SPIFFS.totalBytes());
        }

        json["time"] = getTime();
        String response;
        serializeJson(json, response);
        client->text(response);
    }
}
