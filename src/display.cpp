#include "display.h"


void display_setup()
{
    tft.begin();
    tft.setRotation(1); // Landscape mode
    tft.fillScreen(ILI9341_BLACK);

    // tft.setTextSize(4);
    // tft.setTextColor(ILI9341_WHITE);
    // tft.setCursor(10, 120);
    // tft.println("BME280 Ready...");
}

void showTemperature(float temperature)
{
    tft.fillScreen(ILI9341_WHITE);
    tft.setCursor(40, 20);
    tft.setTextSize(3);
    tft.setTextColor(ILI9341_BLACK);
    tft.println("Temperature");

    tft.fillCircle(65, 170, 50, ILI9341_BLACK);   // cercul de jos
    tft.fillRect(40, 75, 50, 100, ILI9341_BLACK); // dreptunghiul
    tft.fillCircle(65, 75, 25, ILI9341_BLACK);    // cercul de sus

    tft.fillCircle(65, 170, 40, ILI9341_WHITE);  // cercul de jos
    tft.fillRect(50, 75, 30, 80, ILI9341_WHITE); // dreptunghiul
    tft.fillCircle(65, 75, 15, ILI9341_WHITE);   // cercul de sus

    if (temperature <= 15)
    {
        tft.fillCircle(65, 170, 25, ILI9341_BLUE);  // cercul de jos
        tft.fillRect(58, 75, 16, 80, ILI9341_BLUE); // dreptunghiul
        tft.fillCircle(65, 75, 7, ILI9341_BLUE);    // cercul de sus
    }
    else
    {
        tft.fillCircle(65, 170, 25, ILI9341_RED);  // cercul de jos
        tft.fillRect(58, 75, 16, 80, ILI9341_RED); // dreptunghiul
        tft.fillCircle(65, 75, 7, ILI9341_RED);    // cercul de sus
    }

    tft.fillRect(93, 75, 17, 7, ILI9341_BLACK);
    tft.fillRect(93, 85, 10, 7, ILI9341_BLACK);
    tft.fillRect(93, 95, 17, 7, ILI9341_BLACK);
    tft.fillRect(93, 105, 10, 7, ILI9341_BLACK);

    tft.setCursor(125, 120);
    tft.setTextSize(4);
    tft.printf("%.2f C", temperature);
}

void showHumidity(float humidity)
{
    tft.fillScreen(ILI9341_WHITE);
    tft.setCursor(75, 20);
    tft.setTextSize(3);
    tft.setTextColor(ILI9341_BLACK);
    tft.println("Humidity");

    tft.fillCircle(65, 130, 40, ILI9341_LIGHTBLUE);                 // cercul de jos
    tft.fillTriangle(25, 120, 105, 120, 65, 50, ILI9341_LIGHTBLUE); // triunghiul de sus

    tft.fillCircle(65, 130, 30, ILI9341_WHITE);
    tft.fillCircle(65, 120, 35, ILI9341_LIGHTBLUE);

    tft.setCursor(50, 180);
    tft.setTextSize(6);
    tft.setTextColor(ILI9341_LIGHTBLUE);
    tft.printf("%%");

    tft.setCursor(140, 120);
    tft.setTextSize(4);
    tft.setTextColor(ILI9341_BLACK);
    tft.printf("%.2f %%", humidity);
}

void showPressure(float pressure)
{
    tft.fillScreen(ILI9341_WHITE);
    tft.setCursor(70, 20);
    tft.setTextSize(3);
    tft.setTextColor(ILI9341_BLACK);
    tft.println("Pressure");

    tft.fillCircle(13, 70, 10, ILI9341_BLUE); // clouds
    tft.fillCircle(30, 67, 15, ILI9341_BLUE);
    tft.fillCircle(50, 70, 10, ILI9341_BLUE);
    tft.fillRect(13, 67, 35, 15, ILI9341_BLUE);

    tft.fillCircle(100, 70, 17, ILI9341_ORANGE); // sun

    tft.fillCircle(55, 145, 50, ILI9341_BLACK);//barometrul
    tft.fillCircle(55, 145, 45, ILI9341_WHITE);
    tft.fillTriangle(55, 123, 40, 140, 70, 140, ILI9341_BLACK);
    tft.fillTriangle(55, 128, 45, 140, 65, 140, ILI9341_WHITE);
    tft.fillRect(52, 125, 6, 50, ILI9341_BLACK);
    tft. fillRect(75, 145, 15, 6, ILI9341_BLACK);
    tft.fillTriangle(75, 156, 85, 159, 82, 164, ILI9341_BLACK);
    tft.fillTriangle(75, 156, 82, 164, 73, 163, ILI9341_BLACK);

    tft.setCursor(140, 120);
    tft.setTextSize(4);
    tft.setTextColor(ILI9341_BLACK);
    tft.printf("%.2f", pressure);
    tft.setCursor(180, 155);
    tft.setTextSize(4);
    tft.setTextColor(ILI9341_BLACK);
    tft.printf("hPa");
}

void showAltitude(float altitude)
{
    tft.fillScreen(ILI9341_WHITE);
  tft.setCursor(75, 20);
  tft.setTextSize(3);
  tft.setTextColor(ILI9341_BLACK);
  tft.println("Altitude");

  // desen munte
  tft.fillTriangle(5, 210, 135, 210, 75, 65, ILI9341_BROWN);
  tft.fillTriangle(10, 205, 130, 205, 75, 75, ILI9341_WHITE);
  tft.fillTriangle(20, 210, 105, 210, 70, 120, ILI9341_BROWN);
  tft.fillTriangle(80, 210, 127, 210, 100, 160, ILI9341_BROWN);

  // desen sageata
  tft.fillTriangle(90, 65, 120, 65, 105, 50, ILI9341_BLACK);
  tft.fillTriangle(97, 65, 113, 65, 105, 58, ILI9341_WHITE);
  tft.fillRect(102, 55, 7, 30, ILI9341_BLACK);

  tft.setCursor(150, 120);
  tft.setTextSize(4);
  tft.setTextColor(ILI9341_BLACK);
  tft.printf("%.fm", altitude);
}

void showMinMaxTemperature(float minTemp, float maxTemp)
{
    tft.fillScreen(ILI9341_WHITE);
    tft.setCursor(20, 20);
    tft.setTextSize(3);
    tft.setTextColor(ILI9341_BLACK);
    tft.println("Min/Max Temp");

    tft.setCursor(40, 100);
    tft.setTextSize(4);
    tft.setTextColor(ILI9341_BLUE);
    tft.printf("Min: %.2f C", minTemp);

    tft.setCursor(40, 180);
    tft.setTextSize(4);
    tft.setTextColor(ILI9341_RED);
    tft.printf("Max: %.2f C", maxTemp);
}