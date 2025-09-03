#include <WiFi.h>

#include "Connect.h"

#define TFT_CS 5
#define TFT_DC 27
#define TFT_RST 45

#define ILI9341_LIGHTBLUE 0x3B1F
#define ILI9341_BROWN 0x7800



void setup()
{
  delay(1000);
  Serial.begin(115200);
  SetupWIFI();
  SetupTime();
  Serial.println();
  Serial.print(FormatTime());
}

void loop()
{
  // nimic
}
