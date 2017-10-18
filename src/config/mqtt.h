#ifndef MQTT_H_
#define MQTT_H_

#include <ESP8266WiFi.h>

const char *mqtt_server = "m21.cloudmqtt.com";
const int mqtt_port = 17602;
const char *mqtt_user = "test";
const char *mqtt_pass = "test";

const bool retained = false;

String prefix   = "/IoTmanager";
String deviceID = "Dom";

typedef struct
{
  String sTopic;
  String stat;
  bool st;
} vars_type;

enum {
 LED1 = 0,
 LED2,
 WCOUNT
};

vars_type Var[WCOUNT];
String thing_config[WCOUNT];

#endif //MQTT_H_
