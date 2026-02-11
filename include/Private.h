#pragma once

// Structură pentru stocarea credențialelor WiFi
struct WiFiNetwork {
    const char* ssid;
    const char* password;
};

// Vector cu mai multe variante de conexiune WiFi
const WiFiNetwork wifiNetworks[] = {
    {"525", "NuSeSpune"},                    // Red 1
    {"Vodafone_WiFi_Students", "Future8T@len!s"}, // Red 2 (alternativă)
    // Adauga mai multe rețele după necesitate:
    {"Galaxy", "12345678"},
};

const int wifiNetworksCount = sizeof(wifiNetworks) / sizeof(wifiNetworks[0]);