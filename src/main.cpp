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
#include "Processing.hpp"
// #include "Firebase.hpp"


void setup(){
  Serial.begin(115200);

  InitPreferences();
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
  InitOTA();
  InitProcessing();

}

void loop()
{
  ArduinoOTA.handle();
  bot.tick();
}