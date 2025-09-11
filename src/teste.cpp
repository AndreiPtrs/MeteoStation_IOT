#include "sdcard.h"
#include "Altitude.h"
#include"buzz.h"

#define TFT_CS 5
#define TFT_DC 27
#define TFT_RST 14
#define SD_CS 17
#define ILI9341_LIGHTBLUE 0x3B1F
#define ILI9341_BROWN 0x7800

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);


void setup()
{
  initializeSDCard();
  tft.begin();
  tft.setRotation(1); // landscape
}

void loop()
{
  Altitude(500.0);
  delay (2000); // altitudine de referinta in metri
  scriere_sd();
  delay(2000); // log la fiecare 2 secunde
  citire_sd();
  delay(2000);
}
