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

    tft.fillCircle(13, 70, 10, ILI9341_BLUE); // clouds
    tft.fillCircle(30, 67, 15, ILI9341_BLUE);
    tft.fillCircle(50, 70, 10, ILI9341_BLUE);
    tft.fillRect(13, 67, 35, 15, ILI9341_BLUE);

    tft.fillCircle(100, 70, 17, ILI9341_ORANGE); // sun

    tft.fillCircle(55, 145, 50, ILI9341_BLACK);//barometrul
    tft.fillCircle(55, 145, 45, ILI9341_WHITE);
    tft.fillTriangle(55, 123, 40, 140, 70, 140, ILI9341_BLACK);
    tft.fillTriangle(55, 128, 45, 140, 65, 140, ILI9341_WHITE);
    tft.fillRect(52, 125, 6, 50, ILI9341_BLACK);
    tft. fillRect(75, 145, 15, 6, ILI9341_BLACK);
    tft.fillTriangle(75, 156, 85, 159, 82, 164, ILI9341_BLACK);
    tft.fillTriangle(75, 156, 82, 164, 73, 163, ILI9341_BLACK);

    tft.setCursor(140, 120);
    tft.setTextSize(4);
    tft.setTextColor(ILI9341_BLACK);
    tft.printf("%.2f", pressure);
    tft.setCursor(180, 155);
    tft.setTextSize(4);
    tft.setTextColor(ILI9341_BLACK);
    tft.printf("hPa");
}