// #include <ArduinoJson.h>
TimerHandle_t processingTimer;

void processing()
{
    // Temperature and Humidity Processing
    if (Temperature != lastTemperature)
    {
        lastTemperature = Temperature;
        notifyWs("Temperature", Temperature);
        mqttClient.publish(String(MQTT_SUB + "/Temperature").c_str(), 1, true, String(Temperature).c_str());
    }

    if (Humidity != lastHumidity)
    {
        lastHumidity = Humidity;
        notifyWs("Humidity", Humidity);
        mqttClient.publish(String(MQTT_SUB + "/Humidity").c_str(), 1, true, String(Humidity).c_str());
    }

    // Temperature and Humidity MIN MAX Processing
    if (Temperature > temperature_max)
        relay_1 = false;
    else if (Temperature < temperature_min)
        relay_1 = true;

    if (Humidity > humidity_max)
        relay_2 = false;
    else if (Humidity < humidity_min)
        relay_2 = true;

    // Relay Processing
    if (relay_1 != digitalRead(Relay_1))
    {
        digitalWrite(Relay_1, relay_1);
        preferences.putBool("relay_1", relay_1);
        notifyWs("r1", relay_1);
        mqttClient.publish(String(MQTT_SUB + "/r1").c_str(), 1, true, relay_1 ? "1" : "0");
    }

    if (relay_2 != digitalRead(Relay_2))
    {
        digitalWrite(Relay_2, relay_2);
        preferences.putBool("relay_2", relay_2);
        notifyWs("r2", relay_2);
        mqttClient.publish(String(MQTT_SUB + "/r2").c_str(), 1, true, relay_2 ? "1" : "0");
    }

    if (relay_3 != digitalRead(Relay_3))
    {
        digitalWrite(Relay_3, relay_3);
        preferences.putBool("relay_3", relay_3);
        notifyWs("r3", relay_3);
        mqttClient.publish(String(MQTT_SUB + "/r3").c_str(), 1, true, relay_3 ? "1" : "0");
    }

    if (relay_4 != digitalRead(Relay_4))
    {
        digitalWrite(Relay_4, relay_4);
        preferences.putBool("relay_4", relay_4);
        notifyWs("r4", relay_4);
        mqttClient.publish(String(MQTT_SUB + "/r4").c_str(), 1, true, relay_4 ? "1" : "0");
    }

    // Temperature and Humidity MIN MAX Processing
    if ((Temperature > temperature_max + 1 || Temperature < temperature_min - 1) && !warning)
    {
        //bot.sendMessage("🚧 *Warning*, Temperature exceeds the min max.");
        //bot.pinMessage(bot.lastBotMsg());
        warning = true;
    }
}

void InitProcessing()
{
    processingTimer = xTimerCreate("gxhtTimer", pdMS_TO_TICKS(1000), pdTRUE, (void *)0, reinterpret_cast<TimerCallbackFunction_t>(processing));
    xTimerStart(processingTimer, 0);
}