#include "Altitude.h"
#include "Humidity.h"
#include "Pressure.h"
#include "Temperature.h"

#define TFT_CS 5
#define TFT_DC 27
#define TFT_RST 45

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

void setup(){
    tft.begin();
    tft.setRotation(1);
    Pressure(1013.25);
}

void loop(){}