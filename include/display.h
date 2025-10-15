#pragma once

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

#define ILI9341_BROWN 0x7800
#define ILI9341_DARKGREY 0x7BEF
#define ILI9341_LIGHTBLUE 0x3B1F

// Variabilă globală pentru display
extern Adafruit_ILI9341 tft;

// Prototipuri pentru funcțiile de afișare
void display_setup();
void showTemperature(float temperature);
void showHumidity(float humidity);
void showPressure(float pressure);
void showAltitude(float altitude);
void showMinMaxTemperature(float minTemp, float maxTemp);