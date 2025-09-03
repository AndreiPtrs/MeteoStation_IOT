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
