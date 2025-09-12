#include "Temperature.h"
#include "Humidity.h"
#include "buzz.h"
#include "Altitude.h"
#include "Pressure.h"
#include "Connect.h"
#include "sdcard.h"
#include "buzz.h"
#include "bme280.h"
#include "display.h"

// === TFT pins (adjust for your wiring) ===
#define TFT_CS 5
#define TFT_DC 27
#define TFT_RST 14
#define SD_CS 17
#define TFT_BL 33 // Pin for TFT backlight control

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST); // TFT instance
Adafruit_BME280 bme; // BME280 sensor

// === Button pin ===
#define BUTTON_PIN 13

// === timing variables (easy to change) ===
unsigned long sensorInterval = 5000; // sensor read every 5 seconds
unsigned long lastSensorRead = 0;

// sensor data
float temperature, pressure, humidity, altitude;
int page = 0;

// debounce variables
unsigned long lastButtonPress = 0;
const unsigned long debounceDelay = 200; // ms

bool backlightOn = true;
unsigned long buttonPressStart = 0;

void showPage(int pag);

void toggleBacklight() {
    backlightOn = !backlightOn;
    digitalWrite(TFT_BL, backlightOn ? HIGH : LOW);
    Serial.printf("Backlight %s\n", backlightOn ? "ON" : "OFF");
}

void setup()
{
  Serial.begin(115200);
  delay(1000);
  pinMode(BUTTON_PIN, INPUT);
  pinMode (TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH); 

  Serial.println("\n=== ESP32 + BME280 Init ===");
  bme_init();

  display_setup();
}

void loop()
{
  unsigned long now = millis();

  // === detectare apăsare lungă pentru backlight ON/OFF ===
  if (digitalRead(BUTTON_PIN) == HIGH) {
      if (buttonPressStart == 0) buttonPressStart = now;
      if ((now - buttonPressStart) > 3000) { // 3 secunde
          toggleBacklight();
          while (digitalRead(BUTTON_PIN) == HIGH) delay(10); // așteaptă eliberarea butonului
          buttonPressStart = 0;
          lastButtonPress = now;
          return; // evită schimbarea paginii accidental
      }
  } else {
      buttonPressStart = 0;
  }

  // === read sensor data on interval ===
  if (now - lastSensorRead >= sensorInterval)
  {
    lastSensorRead = now;
    bme_measure(temperature, pressure, humidity, altitude);

    Serial.println("===================================");
    Serial.println(" 🌍  BME280 Sensor Data");
    Serial.println("===================================");
    Serial.printf(" 🌡️  Temperature : %.2f °C\n", temperature);
    Serial.printf(" 💧  Humidity    : %.2f %%\n", humidity);
    Serial.printf(" ⬇️  Pressure    : %.2f hPa\n", pressure);
    Serial.printf(" 🏔️  Altitude    : %.2f m\n", altitude);
    Serial.println("===================================\n");

    // Actualizează pagina curentă cu datele noi
    showPage(page);
  }

  // === schimbă pagina la apăsarea butonului ===
  if (digitalRead(BUTTON_PIN) == HIGH && (now - lastButtonPress > debounceDelay) && buttonPressStart == 0)
  {
    lastButtonPress = now;
    page = (page + 1) % 4;
    showPage(page); // afișează noua pagină imediat
    Serial.printf("Pagina schimbata: %d\n", page);
  }
  // buzz();
}

void showPage(int pag)
{
  switch (pag)
  {
  case 0: // 🌡️ Temperature
    showTemperature(temperature);
    break;

  case 1: // 💧 Humidity
    showHumidity(humidity);
    break;

  case 2: // ⬇️ Pressure
    showPressure(pressure);
    break;
  case 3: // 🏔️ Altitude
    showAltitude(altitude);
    break;
  }
}
