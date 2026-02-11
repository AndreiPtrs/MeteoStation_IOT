#include <string>
#include <cstring>

#include "Connect.h"
#include "Private.h"
#include "display.h"
#include "buzz.h"

bool wifiConnected = false; // Flag global pentru starea WiFi
String connectedSSID = ""; // Stochează SSID-ul rețelei conectate

// Funcție pentru a se conecta la prima rețea WiFi disponibilă din vector
void ConnectToAvailableWiFi()
{
    WiFi.mode(WIFI_STA);
    WiFi.disconnect(true); // Deconectează și dezactivează AP
    delay(100);

    Serial.println("\n[WiFi] Scanning for available networks...");
    tft.setTextSize(3);
    tft.fillScreen(ILI9341_BLACK);
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(10, 20);
    tft.println("Scanning WiFi...");

    // Scan pentru rețelele disponibile
    int numNetworks = WiFi.scanNetworks();
    Serial.printf("[WiFi] Found %d networks\n", numNetworks);

    if (numNetworks == 0) {
        Serial.println("[WiFi] No networks found!");
        tft.fillScreen(ILI9341_BLACK);
        tft.setCursor(10, 20);
        tft.setTextColor(ILI9341_RED);
        tft.println("No WiFi found");
        return;
    }

    // Cauta și conectează la prima rețea disponibilă din vector
    bool foundNetwork = false;
    for (int i = 0; i < wifiNetworksCount; i++) {
        for (int j = 0; j < numNetworks; j++) {
            if (strcmp(WiFi.SSID(j).c_str(), wifiNetworks[i].ssid) == 0) {
                Serial.printf("[WiFi] Found network: %s\n", wifiNetworks[i].ssid);
                tft.fillScreen(ILI9341_BLACK);
                tft.setCursor(10, 20);
                tft.setTextColor(ILI9341_WHITE);
                tft.printf("Connecting to:\n%s", wifiNetworks[i].ssid);

                // Se conectează la rețea
                WiFi.begin(wifiNetworks[i].ssid, wifiNetworks[i].password);
                connectedSSID = wifiNetworks[i].ssid;

                unsigned long startTime = millis();
                const unsigned long timeout = 15000; // 15 secunde timeout

                while (WiFi.status() != WL_CONNECTED && (millis() - startTime) < timeout) {
                    delay(500);
                    Serial.print('.');
                    tft.print('.');
                }

                Serial.println();

                if (WiFi.status() == WL_CONNECTED) {
                    wifiConnected = true;
                    foundNetwork = true;

                    tft.fillScreen(ILI9341_BLACK);
                    tft.setCursor(20, 20);
                    tft.setTextSize(3);
                    tft.setTextColor(ILI9341_GREEN);
                    tft.printf("Connected to\n%s", wifiNetworks[i].ssid);
                    connectedbuzz();
                    Serial.printf("[WiFi] Connected to: %s\n", wifiNetworks[i].ssid);
                    Serial.print("[WiFi] IP Address: ");
                    Serial.println(WiFi.localIP());
                    delay(2000);
                    break; // Ieși din bucla de rețele disponibile
                } else {
                    Serial.printf("[WiFi] Failed to connect to %s\n", wifiNetworks[i].ssid);
                    WiFi.disconnect(true);
                    delay(500);
                }
            }
        }
        if (foundNetwork) break; // Ieși din bucla vector dacă s-a conectat
    }

    if (!foundNetwork) {
        wifiConnected = false;
        Serial.println("[WiFi] None of the configured networks were available");
        tft.fillScreen(ILI9341_BLACK);
        tft.setCursor(10, 10);
        tft.setTextSize(3);
        tft.setTextColor(ILI9341_RED);
        tft.println("WiFi offline\nmode");
        unconnectedbuzz();
        delay(2000);
    }
}

// Funcție pentru compatibilitate cu codul existent (apelează noua funcție)
void SetupWIFI()
{
    ConnectToAvailableWiFi();
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