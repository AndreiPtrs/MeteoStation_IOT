#include <string>

#include "Connect.h"
#include "Private.h"
#include "display.h"

bool wifiConnected = false; // Flag global pentru starea WiFi

void SetupWIFI()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    Serial.print("Connecting to WiFi ..");
    tft.setTextSize(4);
    tft.fillScreen(ILI9341_BLACK);
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(2, 20);
    tft.printf("Connecting to WiFi, %s", ssid);
    
    unsigned long startTime = millis();
    const unsigned long timeout = 15000; // 15 secunde timeout

    while (WiFi.status() != WL_CONNECTED && (millis() - startTime) < timeout)
    {
        delay(500);
        Serial.print('.');
        tft.print('.'); // Afișează puncte pe ecran pentru a indica încercarea de conectare
    }

    Serial.println();
    
    if (WiFi.status() == WL_CONNECTED) {
        wifiConnected = true;

        tft.fillScreen(ILI9341_BLACK);
        tft.setCursor(20, 20);
        tft.setTextSize(4);
        tft.setTextColor(ILI9341_GREEN);
        tft.printf("Connected to WiFi, %s", ssid);
        
        Serial.printf("Connected to the WiFi, %s", ssid);
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
        
        
    } else {
        wifiConnected = false;
        Serial.println("WiFi connection timeout after 15 seconds");
        Serial.println("Continuing without WiFi...");
        
        tft.fillScreen(ILI9341_BLACK);
        tft.setCursor(10, 10);
        tft.setTextSize(4);
        tft.setTextColor(ILI9341_RED);
        tft.println("WiFi timeout\noffline mode");
        
        delay(1000); // Afișează mesajul pentru 1 secundă
    }
}

const int gmtOffset_sec = 7200;
const int daylightOffset = 3600;

void SetupTime()
{
    if (!wifiConnected) {
        Serial.println("No WiFi - skipping time sync");
        return;
    }
    
    configTime(gmtOffset_sec, daylightOffset, "pool.ntp.org", "time.nist.gov");
    Serial.print("Sync time...");
    struct tm timeinfo;
    while (!getLocalTime(&timeinfo))
    {
        Serial.print(".");
        delay(500);
    }
    Serial.println("OK");
}

String FormatTime()
{
    struct tm timeinfo;
    getLocalTime(&timeinfo);
    char buf[30];
    strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%SZ", &timeinfo);
    return String(buf);
}

const char* MQTT_HOST = "mqtt.aiot-xplorer.eu"; // Ip broker
const uint16_t MQTT_PORT = 1883;

WiFiClient espClient; 
PubSubClient mqtt(espClient);

void setupMQTT()
{
    if (!wifiConnected) {
        Serial.println("No WiFi - skipping MQTT setup");
        return;
    }
    mqtt.setServer(MQTT_HOST, MQTT_PORT);
}

void connectMQTT()
{
    if (!wifiConnected) {
        Serial.println("No WiFi - skipping MQTT connection");
        return;
    }
    
    while (!mqtt.connected())
    {
        Serial.print("Connecting to MQTT...");
        if (mqtt.connect("esp32-client"))
        {
            Serial.println();
            Serial.println("connected");
        }
        else
        {
            Serial.print(".");
            delay(1000);
        }
    }
}

void sendData(PubSubClient &mqttClient, const char* topic, const char* sensor, float value, const char* unit)
{
    if (!wifiConnected || !mqtt.connected()) {
        Serial.println("No WiFi/MQTT connection - data not sent");
        return;
    }
    
    StaticJsonDocument<200> doc;
    doc["ts"] = FormatTime();
    doc["value"] = value;
    doc["unit"] = unit;
    doc["sensor"] = sensor;
    char buffer[200];
    size_t n = serializeJson(doc, buffer);

    mqttClient.publish(topic, buffer, n);

    Serial.printf("Published to %s: %s\n", topic, buffer);
}