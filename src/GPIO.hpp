void InitGPIO()
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