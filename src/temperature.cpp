#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

extern Adafruit_ILI9341 tft;

void Temperature(float temperature)
{
      tft.fillScreen(ILI9341_WHITE);
      tft.setCursor(40, 20);
      tft.setTextSize(3);
      tft.setTextColor(ILI9341_BLACK);
      tft.println("Temperature");

      tft.fillCircle(65, 170, 50, ILI9341_BLACK);   // cercul de jos
      tft.fillRect(40, 75, 50, 100, ILI9341_BLACK); // dreptunghiul
      tft.fillCircle(65, 75, 25, ILI9341_BLACK);    // cercul de sus

      tft.fillCircle(65, 170, 40, ILI9341_WHITE);  // cercul de jos
      tft.fillRect(50, 75, 30, 80, ILI9341_WHITE); // dreptunghiul
      tft.fillCircle(65, 75, 15, ILI9341_WHITE);   // cercul de sus

      if (temperature <= 15)
      {
            tft.fillCircle(65, 170, 25, ILI9341_BLUE);  // cercul de jos
            tft.fillRect(58, 75, 16, 80, ILI9341_BLUE); // dreptunghiul
            tft.fillCircle(65, 75, 7, ILI9341_BLUE);    // cercul de sus
      }
      else
      {
            tft.fillCircle(65, 170, 25, ILI9341_RED);  // cercul de jos
            tft.fillRect(58, 75, 16, 80, ILI9341_RED); // dreptunghiul
            tft.fillCircle(65, 75, 7, ILI9341_RED);    // cercul de sus
      }

      tft.fillRect(93, 75, 17, 7, ILI9341_BLACK);
      tft.fillRect(93, 85, 10, 7, ILI9341_BLACK);
      tft.fillRect(93, 95, 17, 7, ILI9341_BLACK);
      tft.fillRect(93, 105, 10, 7, ILI9341_BLACK);

      tft.setCursor(125, 120);
      tft.setTextSize(4);
      tft.printf("%.2f C", temperature);
}
