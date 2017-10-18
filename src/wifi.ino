#include "config/include.h"

void WIFI_Loop() {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.printf("[WIFI] Connecting to WiFi...\n");
        WiFi.mode(WIFI_STA);
        WiFi.begin(SSID, PASSWORD);

        if (WiFi.waitForConnectResult() != WL_CONNECTED) return;
        IPAddress myIP = WiFi.localIP();
        Serial.printf("[WIFI] WiFi connected\n");
        Serial.printf("[WIFI] IP address: %d.%d.%d.%d\n",myIP[0],myIP[1],myIP[2],myIP[3]);
        }
}
