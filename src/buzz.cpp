#pragma once Humidity.cpp
 
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

extern Adafruit_ILI9341 tft;
const int buzzerPin = 32; // Pinul la care este conectat buzzer-ul

void buzz(){
  // cresc frecvența de la 1000 Hz la 2000 Hz
  for(int freq = 1000; freq <= 2000; freq += 50){
    tone(buzzerPin, freq);
    delay(20);
  }

  // scade frecvența de la 2000 Hz la 1000 Hz
  for(int freq = 2000; freq >= 1000; freq -= 50){
    tone(buzzerPin, freq);
    delay(20);
  }
};
