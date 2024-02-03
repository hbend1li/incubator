#include <Arduino.h>

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <AsyncMqttClient.h>
#include <WiFiClientSecure.h>
#include <SPIFFS.h>
#include <ESPmDNS.h>

#include "StoredPreferences.hpp"
#include "time.h"
#include "MQTT.hpp"
#include "ESP32_Utils.hpp"
#include "ESP32_Utils_MQTT_Async.hpp"
#include "ESP32_Utils_mDNS.hpp"
#include "TelegramBot.hpp"
#include "Api.hpp"
#include "Gxht.hpp"
#include "Server.hpp"

void setup()
{
  Serial.begin(115200);
  SPIFFS.begin();

  InitPreferences();
  InitHardware();
  InitGxht();
  InitTime();
  InitMqtt();
  InitWifi();
  InitServer();
  InitMDNS();

  mqttClient.publish(String(MQTT_SUB + "/start").c_str(), 1, true, "1");
}

void loop()
{
}