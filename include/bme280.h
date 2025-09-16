#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_ILI9341.h>

#define BME_SDA 21
#define BME_SCL 22
#define SEALEVELPRESSURE_HPA (1013.25)

extern Adafruit_BME280 bme;

void bme_init();
void bme_measure(float &temperature, float &pressure, float &humidity, float &altitude);
    

