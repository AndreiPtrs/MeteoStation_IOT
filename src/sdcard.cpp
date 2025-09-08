#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_ILI9341.h>

extern Adafruit_ILI9341 tft;
// Define SPI and SD card pins if not already defined
#define SD_CS 17 // Change this to your SD card CS pin

Adafruit_BME280 bme; // Global BME280 sensor object

void initializeSDCard()
{
    Serial.begin(115200);
    Serial.print("Initializare card SD...");
    SPI.begin(); // Use default SPI pins
    if (!SD.begin(SD_CS, SPI))
    {
        Serial.println("Eroare la accesarea cardului SD!");
        while (1)
            ;
    }
    Serial.println("Card SD detectat.");
    File dataFile = SD.open("/bme280_log.csv", FILE_APPEND);
    if (dataFile && dataFile.size() == 0)
    {
        dataFile.println("Timp(ms),Temperatura[C],Presiune[hPa],Umiditate[%]");
        dataFile.close();
    }

    // Initialize BME280 sensor
    if (!bme.begin(0x76) && !bme.begin(0x77)) { // Default I2C address is 0x76 or 0x77
        Serial.println("Nu s-a detectat senzorul BME280!");
        while (1);
    }
}

void scriere_sd()
{
    float temperatura = bme.readTemperature();
  float presiune = bme.readPressure() / 100.0F;
  float umiditate = bme.readHumidity();

  Serial.print("T=");
  Serial.print(temperatura);
  Serial.print(" *C, P=");
  Serial.print(presiune);
  Serial.print(" hPa, H=");
  Serial.print(umiditate);
  Serial.println(" %");

  File dataFile = SD.open("/bme280_log.csv", FILE_APPEND);
  if (dataFile) {
    dataFile.print(millis());
    dataFile.print(",");
    dataFile.print(temperatura);
    dataFile.print(",");
    dataFile.print(presiune);
    dataFile.print(",");
    dataFile.println(umiditate);
    dataFile.close();
  } else {
    Serial.println("Nu pot scrie pe card!");
  }

}
