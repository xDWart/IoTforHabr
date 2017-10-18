#include "config/include.h"

void setup() {
  bootSetup();
  ledSetup();
  initVar();
}

void loop() {
  WIFI_Loop();
  MQTT_loop();
}
