#include <string>

#include "Connect.h"
#include "Private.h"

void SetupWIFI()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    Serial.print("Connecting to WiFi ..");

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print('.');
    }

    Serial.println();
    Serial.println("Connected to the WiFi network");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}

const int gmtOffset_sec = 7200;
const int daylightOffset = 3600;

void SetupTime()
{
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
    mqtt.setServer(MQTT_HOST, MQTT_PORT);
}

void connectMQTT()
{
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