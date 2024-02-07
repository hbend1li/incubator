#include <Wire.h>

#define gxht30Addr 0x44

TimerHandle_t gxhtReadTimer;

void ReadGxht()
{
    xTimerStart(gxhtReadTimer, 0);
    unsigned int data[6];
    // Start I2C Transmission
    Wire.beginTransmission(gxht30Addr);
    // Send measurement command
    Wire.write(0x2C); // MSB
    Wire.write(0x06); // LSB
    // Stop I2C transmission
    Wire.endTransmission();

    delay(500);

    // Request 6 bytes of data
    Wire.requestFrom(gxht30Addr, 6);

    // Read 6 bytes of data
    // cTemp msb, cTemp lsb, cTemp crc, humidity msb, humidity lsb, humidity crc
    if (Wire.available() == 6)
    {
        data[0] = Wire.read();
        data[1] = Wire.read();
        data[2] = Wire.read();
        data[3] = Wire.read();
        data[4] = Wire.read();
        data[5] = Wire.read();
    }
    
    // Convert the data
    Temperature = ((((data[0] * 256.0) + data[1]) * 175) / 65535.0) - 45;
    Humidity = ((((data[3] * 256.0) + data[4]) * 100) / 65535.0);
}

void InitGxht()
{
    Wire.begin();
    Wire.beginTransmission(gxht30Addr);
    Wire.endTransmission();

    gxhtReadTimer = xTimerCreate("gxhtTimer", pdMS_TO_TICKS(1000), pdFALSE, (void *)0, reinterpret_cast<TimerCallbackFunction_t>(ReadGxht));
    xTimerStart(gxhtReadTimer, 0);
    //ReadGxht();
}