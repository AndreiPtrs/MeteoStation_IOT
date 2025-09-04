#include "Humidity.h"

extern Adafruit_ILI9341 tft;
#define ILI9341_LIGHTBLUE 0x3B1F

void Humidity(float humidity)
{
    tft.fillScreen(ILI9341_WHITE);
    tft.setCursor(75, 20);
    tft.setTextSize(3);
    tft.setTextColor(ILI9341_BLACK);
    tft.println("Humidity");

    tft.fillCircle(65, 130, 40, ILI9341_LIGHTBLUE);                 // cercul de jos
    tft.fillTriangle(25, 120, 105, 120, 65, 50, ILI9341_LIGHTBLUE); // triunghiul de sus

    tft.fillCircle(65, 130, 30, ILI9341_WHITE);
    tft.fillCircle(65, 120, 35, ILI9341_LIGHTBLUE);

    tft.setCursor(50, 180);
    tft.setTextSize(6);
    tft.setTextColor(ILI9341_LIGHTBLUE);
    tft.printf("%%");

    tft.setCursor(140, 120);
    tft.setTextSize(4);
    tft.setTextColor(ILI9341_BLACK);
    tft.printf("%.2f %%", humidity);
}