#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_ILI9341.h>

extern Adafruit_ILI9341 tft;

void bme_masurare(float &temperatura, float &presiune, float &umiditate);
    

