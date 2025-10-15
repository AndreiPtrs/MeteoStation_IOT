#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

extern Adafruit_ILI9341 tft;
const int buzzerPin = 14; // Pinul la care este conectat buzzer-ul

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
void shortBuzz(){
  tone(buzzerPin, 2000); // Emite un ton de 2000 Hz
  delay(100);            // Durata tonului
  noTone(buzzerPin);     // Oprește tonul
}

void doubleBuzz(){
  for(int i = 0; i < 2; i++){
    tone(buzzerPin, 2000); // Emite un ton de 2000 Hz
    delay(100);            // Durata tonului
    noTone(buzzerPin);     // Oprește tonul
    delay(100);            // Pauză între tonuri
  }
}

void connectedbuzz(){
  for(int i = 0; i < 3; i++){
    tone(buzzerPin, 1000 + i * 500); // Emite un ton de frecvență crescătoare
    delay(100);                      // Durata tonului
    noTone(buzzerPin);               // Oprește tonul
    delay(50);                       // Pauză între tonuri
  }
}

void unconnectedbuzz(){
  // Sunet scurt descrescător de la frecvență mică (ton de eroare simplu)
  for(int freq = 500; freq >= 200; freq -= 30){
    tone(buzzerPin, freq);
    delay(30);
  }
  noTone(buzzerPin);
}