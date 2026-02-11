#pragma once

#include <WiFi.h>
#include <time.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "Private.h"

extern PubSubClient mqtt;

void SetupWIFI();
void ConnectToAvailableWiFi();
void SetupTime();
String FormatTime();

void setupMQTT();
void connectMQTT();

void sendData(PubSubClient &mqttClient, const char* topic, const char* sensor, float value, const char* unit);