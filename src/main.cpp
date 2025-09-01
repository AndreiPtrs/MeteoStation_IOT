#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

#include "Temperature.h"
#include "Humidity.h"

// === TFT pins (adjust for your wiring) ===
#define TFT_CS 5
#define TFT_DC 27
#define TFT_RST 45

// extra colors
#define ILI9341_BROWN 0xA145
#define ILI9341_DARKGREY 0x7BEF

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

// BME280 sensor
Adafruit_BME280 bme;

// === timing variables (easy to change) ===
unsigned long sensorInterval = 12000;  // sensor read every 5 seconds
unsigned long pageInterval = 3000;     // page changes every 2 seconds

unsigned long lastSensorRead = 0;
unsigned long lastPageChange = 0;

// sensor data
float temperature, pressure, humidity, altitude;

// current page
int page = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("\n=== ESP32 + BME280 Init ===");

  if (!bme.begin(0x76) && !bme.begin(0x77)) {
    Serial.println("BME280 not found!");
    while (1)
      ;
  }

  Serial.println("BME280 detected successfully!\n");

  // TFT init
  tft.begin();
  tft.setRotation(1);  // landscape
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextSize(3);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(20, 20);
  tft.println("BME280 Ready...");
}
void showPage(int pag);

void loop() {
  unsigned long now = millis();

  // === read sensor data on interval ===
  if (now - lastSensorRead >= sensorInterval) {
    lastSensorRead = now;

    temperature = bme.readTemperature();
    pressure = bme.readPressure() / 100.0F;
    humidity = bme.readHumidity();
    altitude = bme.readAltitude(1013.25);

    // Serial monitor output
    Serial.println("===================================");
    Serial.println(" 🌍  BME280 Sensor Data");
    Serial.println("===================================");
    Serial.printf(" 🌡️  Temperature : %.2f °C\n", temperature);
    Serial.printf(" 💧  Humidity    : %.2f %%\n", humidity);
    Serial.printf(" ⬇️  Pressure    : %.2f hPa\n", pressure);
    Serial.printf(" 🏔️  Altitude    : %.2f m\n", altitude);
    Serial.println("===================================\n");
  }

  // === change page on interval ===
  if (now - lastPageChange >= pageInterval) {
    lastPageChange = now;
    showPage(page);
    page = (page + 1) % 4;
  }
}

void showPage(int pag) {
  tft.fillScreen(ILI9341_BLACK);

  switch (pag) {
    case 0:  // 🌡️ Temp erature
      Temperature(temperature);
      break;

    case 1:  // 💧 Humidity
      Humidity(humidity);
      break;

    case 2:  // ⬇️ Pressure
      tft.fillScreen(ILI9341_GREEN);
      tft.setCursor(60, 20);
      tft.setTextSize(3);
      tft.setTextColor(ILI9341_BLACK);
      tft.println("Pressure");

      tft.drawCircle(80, 140, 50, ILI9341_BLACK);
      tft.drawLine(80, 140, 120, 100, ILI9341_BLACK);

      tft.setCursor(140, 120);
      tft.setTextSize(3);
      tft.setTextColor(ILI9341_WHITE);
      tft.printf("%.2f hPa", pressure);
      break;

    case 3:  // 🏔️ Altitude
      tft.fillScreen(ILI9341_YELLOW);
      tft.setCursor(75, 20);
      tft.setTextSize(3);
      tft.setTextColor(ILI9341_BLACK);
      tft.println("Altitude");

      tft.fillTriangle(40, 200, 100, 80, 160, 200, ILI9341_BROWN);
      tft.fillTriangle(120, 200, 200, 100, 280, 200, ILI9341_DARKGREY);

      tft.fillTriangle(90, 110, 100, 80, 110, 110, ILI9341_WHITE);
      tft.fillTriangle(180, 120, 200, 100, 220, 120, ILI9341_WHITE);

      tft.setCursor(60, 220);
      tft.setTextSize(3);
      tft.setTextColor(ILI9341_BLACK);
      tft.printf("%.2f m", altitude);
      break;
  }
}
