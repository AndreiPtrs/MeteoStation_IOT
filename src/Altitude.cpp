#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

extern Adafruit_ILI9341 tft;

#define ILI9341_BROWN 0x7800
#define ILI9341_DARKGREY 0x7BEF

void Altitude(float altitude){
    tft.fillScreen(ILI9341_WHITE);
  tft.setCursor(75, 20);
  tft.setTextSize(3);
  tft.setTextColor(ILI9341_BLACK);
  tft.println("Altitude");

// desen munte
  tft.fillTriangle(5, 210, 135, 210, 75, 65, ILI9341_BROWN);
  tft.fillTriangle(10, 205, 130, 205, 75, 75, ILI9341_WHITE);
  tft.fillTriangle(20, 210, 105, 210, 70, 120, ILI9341_BROWN);
  tft.fillTriangle(80, 210, 127, 210, 100, 160, ILI9341_BROWN);

  //desen sageata
  tft.fillTriangle(90, 65, 120, 65, 105, 50, ILI9341_BLACK);
  tft.fillTriangle(97, 65, 113, 65, 105, 58, ILI9341_WHITE);
  tft.fillRect(102, 55, 7, 30, ILI9341_BLACK);


  tft.setCursor(150, 120);
  tft.setTextSize(4);
  tft.setTextColor(ILI9341_BLACK);
  tft.printf("%.fm", altitude);
}