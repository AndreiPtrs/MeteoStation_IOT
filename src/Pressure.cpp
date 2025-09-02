#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

extern Adafruit_ILI9341 tft;

void Pressure(float pressure)
{
    tft.fillScreen(ILI9341_WHITE);
    tft.setCursor(70, 20);
    tft.setTextSize(3);
    tft.setTextColor(ILI9341_BLACK);
    tft.println("Pressure");
}