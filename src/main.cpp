#include <Arduino.h>

#include "define.h"
#include "Preferences.hpp"
#include "GPIO.hpp"
#include "Gxht.hpp"
#include "MQTT.hpp"

#include "ESP32_Utils_Wifi.hpp"
#include "ESP32_Utils_NTP.hpp"
#include "ESP32_Utils_MQTT_Async.hpp"
#include "ESP32_Utils_mDNS.hpp"
#include "ESP32_Utils_WebServer.hpp"
#include "ESP32_Utils_WebSocket_Async.hpp"

#include "Processing.hpp"
// #include "TelegramBot.hpp"
// #include "Firebase.hpp"

void setup()
{
  Serial.begin(115200);
  

  InitPreferences();
  InitGPIO();
  InitGxht();
  InitMqtt();
  InitWifi();
  InitTime();
  InitMDNS();
  InitWebServer();
  InitWebSockets();
  // InitFirebase();
  // InitTelegram();

  mqttClient.publish(String(MQTT_SUB + "/start").c_str(), 1, true, "1");
}

void loop()
{
  processing();
}