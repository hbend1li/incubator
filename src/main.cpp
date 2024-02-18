#include <Arduino.h>
#include <ArduinoOTA.h>
#include <ESP32Servo.h>

#include "define.h"
#include "Preferences.hpp"
#include "GPIO.hpp"
#include "Gxht.hpp"
#include "MQTT.hpp"
#include "DayNight.hpp"

#include "ESP32_Utils_Wifi.hpp"
#include "ESP32_Utils_NTP.hpp"
#include "ESP32_Utils_MQTT_Async.hpp"
#include "ESP32_Utils_mDNS.hpp"
#include "ESP32_Utils_WebServer.hpp"
#include "ESP32_Utils_WebSocket_Async.hpp"
#include "ESP32_Utils_OTA.hpp"

#include "TelegramBot.hpp"
#include "ProtonIOT.hpp"
// #include "Firebase.hpp"
#include "Processing.hpp"

void setup()
{
  Serial.begin(115200);

  InitPreferences();
  // ResetPreferences();
  InitGPIO();
  InitDayNight();
  InitGxht();
  InitMqtt();
  InitWifi();
  InitTime();
  InitMDNS();
  InitWebServer();
  InitWebSockets();
  // InitFirebase();
  InitTelegram();
  //InitOTA();
  InitProcessing();
  InitCloudIot();
}

void loop()
{
  ArduinoOTA.handle();
  bot.tick();
}