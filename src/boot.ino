#include "config/include.h"

void bootSetup() {
    Serial.begin(SERIAL_BAUDRATE);
    delay(100);
    Serial.printf("\n");
    Serial.printf("[BOOT] %s v.%s\n", (char *) APP_NAME, (char *) APP_VERSION);
    Serial.printf("[BOOT] Memory size: %d bytes\n", ESP.getFlashChipSize());
    Serial.printf("[BOOT] Free heap: %d bytes\n", ESP.getFreeHeap());
    Serial.printf("[BOOT] Firmware size: %d bytes\n", ESP.getSketchSize());
    Serial.printf("[BOOT] Free firmware space: %d bytes\n", ESP.getFreeSketchSpace());
}
