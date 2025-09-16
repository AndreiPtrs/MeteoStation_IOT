#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_ILI9341.h>

extern Adafruit_ILI9341 tft;

void scriere_sd(float &temperature, float &pressure, float &humidity);
void citire_sd();
void initializeSDCard();