#include "sdcard.h"

#define TFT_CS 5
#define TFT_DC 27
#define TFT_RST 45
#define SD_CS 17
#define ILI9341_LIGHTBLUE 0x3B1F
#define ILI9341_BROWN 0x7800

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);


void setup()
{
  initializeSDCard();
}

void loop()
{
  scriere_sd();
  delay(2000); // log la fiecare 2 secunde
}
