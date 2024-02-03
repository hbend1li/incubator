void relayProcess()
{
    if (Temperature > temperature_max && relay_1)
    {
        relay_1 = false;
        digitalWrite(Relay_1, relay_1);
        mqttClient.publish(String(MQTT_SUB + "/r1").c_str(), 1, true, "0");
    }
    else if (Temperature < temperature_min && !relay_1)
    {
        relay_1 = true;
        digitalWrite(Relay_1, relay_1);
        mqttClient.publish(String(MQTT_SUB + "/r1").c_str(), 1, true, "1");
    }

    if (Humidity > humidity_max && relay_4)
    {
        relay_4 = false;
        digitalWrite(Relay_4, relay_4);
        mqttClient.publish(String(MQTT_SUB + "/r4").c_str(), 1, true, "0");
    }
    else if (Humidity < humidity_min && !relay_4)
    {
        relay_4 = true;
        digitalWrite(Relay_4, relay_4);
        mqttClient.publish(String(MQTT_SUB + "/r4").c_str(), 1, true, "1");
    }

    if ((relay_1 && !digitalRead(Relay_1)) || (!relay_1 && digitalRead(Relay_1)))
    {
        digitalWrite(Relay_1, relay_1);
        mqttClient.publish(String(MQTT_SUB + "/r1").c_str(), 1, true, relay_1 ? "1" : "0");
    }

    if ((relay_2 && !digitalRead(Relay_2)) || (!relay_2 && digitalRead(Relay_2)))
    {
        digitalWrite(Relay_2, relay_2);
        mqttClient.publish(String(MQTT_SUB + "/r2").c_str(), 1, true, relay_2 ? "1" : "0");
    }

    if ((relay_3 && !digitalRead(Relay_3)) || (!relay_3 && digitalRead(Relay_3)))
    {
        digitalWrite(Relay_3, relay_3);
        mqttClient.publish(String(MQTT_SUB + "/r3").c_str(), 1, true, relay_3 ? "1" : "0");
    }

    if ((relay_4 && !digitalRead(Relay_4)) || (!relay_4 && digitalRead(Relay_4)))
    {
        digitalWrite(Relay_4, relay_4);
        mqttClient.publish(String(MQTT_SUB + "/r4").c_str(), 1, true, relay_4 ? "1" : "0");
    }
}

void InitHardware()
{
    pinMode(Relay_1, OUTPUT);
    pinMode(Relay_2, OUTPUT);
    pinMode(Relay_3, OUTPUT);
    pinMode(Relay_4, OUTPUT);
    digitalWrite(Relay_1, relay_1);
    digitalWrite(Relay_2, relay_2);
    digitalWrite(Relay_3, relay_3);
    digitalWrite(Relay_4, relay_4);
}

void setGPIO(String id, bool state)
{
    Serial.print("Set GPIO ");
    Serial.print(id);
    Serial.print(": ");
    Serial.println(state);
}

void setPWM(String id, int pwm)
{
    Serial.print("Set PWM ");
    Serial.print(id);
    Serial.print(": ");
    Serial.println(pwm);
}

void doAction(String actionId)
{
    Serial.print("Doing action: ");
    Serial.println(actionId);
}