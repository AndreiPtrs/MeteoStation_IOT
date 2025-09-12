#include <Adafruit_BME280.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ILI9341.h>

#define BME_SDA 21
#define BME_SCL 22
#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;

void bme_masurare(float &temperatura, float &presiune, float &umiditate) {
    temperatura = bme.readTemperature();
    presiune = bme.readPressure() / 100.0F;
    umiditate = bme.readHumidity();
}