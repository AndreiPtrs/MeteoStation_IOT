#include "bme280.h"


void bme_init()
{
    Wire.begin(BME_SDA, BME_SCL);
    if (!bme.begin(0x76) && !bme.begin(0x77))
    {
        Serial.println("BME280 sensor not detected!");
        while (1);
    }
    Serial.println("BME280 sensor detected successfully!");
}

void bme_measure(float &temperature, float &pressure, float &humidity, float &altitude)
{
    temperature = bme.readTemperature();
    pressure = bme.readPressure() / 100.0F;
    humidity = bme.readHumidity();
    altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
}