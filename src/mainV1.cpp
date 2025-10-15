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
#define TFT_RST 25
#define SD_CS 17
#define TFT_BL 33 // Pin for TFT backlight control

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST); // TFT instance
Adafruit_BME280 bme; // BME280 sensor

// === Button pin ===
#define BUTTON_PIN 13

// === timing variables ===
unsigned long sensorInterval = 5000; // sensor read every 5 seconds
unsigned long lastSensorRead = 0;

// sensor data
float temperature, pressure, humidity, altitude;
int page = 0;

// debounce variables
unsigned long lastButtonPress = 0;
const unsigned long debounceDelay = 20; // ms

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
  shortBuzz();
  Serial.begin(115200);
  
  delay(1000);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode (TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH); 

  display_setup();

  SetupWIFI();// connect to WiFi
  SetupTime();

  Serial.println();
  Serial.print(FormatTime());
  Serial.println();

  setupMQTT(); // setup MQTT
  connectMQTT();

  Serial.println("\n=== ESP32 + BME280 Init ===");
  bme_init();

  
}

void loop()
{
  unsigned long now = millis();
  static bool buttonState = HIGH;
  static bool lastButtonState = HIGH;
  static bool buttonPressed = false;
  static unsigned long pressStartTime = 0;
  static bool longPressHandled = false;

  // Citire stare buton cu debounce
  bool reading = digitalRead(BUTTON_PIN);
  
  if (reading != lastButtonState) {
    pressStartTime = now; // resetează timpul la orice schimbare
  }
  
  if ((now - pressStartTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      
      // Detectare început apăsare
      if (buttonState == LOW && !buttonPressed) {
        buttonPressed = true;
        buttonPressStart = now;
        longPressHandled = false;
      }
      
      // Detectare eliberare buton
      if (buttonState == HIGH && buttonPressed) {
        buttonPressed = false;
        unsigned long pressDuration = now - buttonPressStart;
        
        if (!longPressHandled && pressDuration < 2000) {
          // Apăsare scurtă - schimbă pagina
          page = (page + 1) % 5;
          showPage(page);
          Serial.printf("Pagina schimbata: %d (durata: %lu ms)\n", page, pressDuration);
        }
        
        buttonPressStart = 0;
        longPressHandled = false;
      }
    }
  }
  
  // Verificare apăsare lungă în timpul apăsării
  if (buttonPressed && !longPressHandled && (now - buttonPressStart) > 2000) {
    toggleBacklight();
    longPressHandled = true;
    Serial.println("Apasare lunga - toggle backlight");
  }
  
  lastButtonState = reading;

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

    sendData(mqtt, "tenants/delta/mountain/esp32-Delta/temperature", "bme280", temperature, "°C");
    sendData(mqtt, "tenants/delta/mountain/esp32-Delta/humidity", "bme280", humidity, "%");
    sendData(mqtt, "tenants/delta/mountain/esp32-Delta/pressure", "bme280", pressure, "hPa ");
    sendData(mqtt, "tenants/delta/mountain/esp32-Delta/altitude", "bme280", altitude, "m");

    // Actualizează pagina curentă cu datele noi
    showPage(page);
  }
}

void showPage(int pag)
{
  float minTemperature = 25;
  float maxTemperature = 20;
  ;
  switch (pag)
  {
  case 0: // 🌡️ Temperature
    showTemperature(temperature);
    break;

  // case 1: // 🌡️ Min/Max Temperature
  //   showMinMaxTemperature(minTemperature , maxTemperature);
  //   break;
  case 2: // 💧 Humidity
    showHumidity(humidity);
    break;

  case 3: // ⬇️ Pressure
    showPressure(pressure);
    break;
  case 4: // 🏔️ Altitude
    showAltitude(altitude);
    break;
  }
}
