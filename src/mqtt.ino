#include "config/include.h"

//===================vars=================
WiFiClient wifiClient;
PubSubClient client(wifiClient, mqtt_server, mqtt_port);
WiFiClientSecure httpClient;

void initVar() {
  DynamicJsonBuffer jsonBuffer;

  JsonObject& root = jsonBuffer.createObject();
  Var[LED1].sTopic = prefix + "/" + deviceID + "/led1";
  setStatus(&Var[LED1], false);
  root["id"] = String(LED1);
  root["widget"] = "toggle";
  root["topic"]  = Var[LED1].sTopic;
  root["descr"]  = "Светодиод 1";
  root["style1"] = "padding-top:10px;";
  root["descrStyle"] = "font-size:20px;";
  root.printTo(thing_config[LED1]);

  Var[LED2].sTopic = prefix + "/" + deviceID + "/led2";
  setStatus(&Var[LED2], false);
  root["id"] = String(LED2);
  root["widget"] = "toggle";
  root["topic"]  = Var[LED2].sTopic;
  root["descr"]  = "Светодиод 2";
  root["style1"] = "padding-top:10px;";
  root["descrStyle"] = "font-size:20px;";
  root.printTo(thing_config[LED2]);
}

void setStatus(vars_type * var, bool s) {
    var->st = s;
    var->stat = "{\"status\":\"" + String(s) + "\"}";
}

void pubStatus(String t, String payload) {
    if (client.publish((t + "/status").c_str(), (uint8_t*)payload.c_str(), payload.length(), retained)) {
       Serial.println("Publish new status for " + t + ", value: " + payload);
    } else {
       Serial.println("Publish new status for " + t + " FAIL!");
    }
}

void pubConfig() {
     bool success;
     for (char i = 0; i < WCOUNT; i++) {
        success = client.publish((prefix + "/" + deviceID + String(i, DEC) + "/config").c_str(), (uint8_t*)thing_config[i].c_str(), thing_config[i].length(), retained);
        if (success) {
          Serial.println("Publish config: Success (" + thing_config[i] + ")");
        } else {
          Serial.println("Publish config FAIL! ("    + thing_config[i] + ")");
        }
        delay(150);
     }

     for (char i = 0; i < WCOUNT; i++) {
        pubStatus(Var[i].sTopic, Var[i].stat);
        delay(100);
     }
}

void callback(const MQTT::Publish& sub) {
    Serial.print("Message arrived [");
    Serial.print(sub.topic());
    Serial.print("] ");
    Serial.println(sub.payload_string());

    if (sub.topic() == Var[LED1].sTopic + "/control") {
        if (sub.payload_string() == "0") ledStatus(ESP_LED, false);
                                    else ledStatus(ESP_LED, true);
    } else if (sub.topic() == Var[LED2].sTopic + "/control") {
        if (sub.payload_string() == "0") ledStatus(NODE_LED, false);
                                    else ledStatus(NODE_LED, true);
    } else if (sub.topic() == prefix) {
          if (sub.payload_string() == "HELLO") {
            pubConfig();
          }
    }
}

void MQTT_loop() {
    if (WiFi.status() == WL_CONNECTED) {
        if (!client.connected()) {
            Serial.print("Connecting to MQTT server ... ");
            if (client.connect(MQTT::Connect("ESP8266Client").set_auth(mqtt_user,mqtt_pass))){
                client.set_callback(callback);
                Serial.println("Success");
                client.subscribe(prefix.c_str());
                for (char i = 0; i < WCOUNT; i++) {
                    client.subscribe((Var[i].sTopic + "/control").c_str());
                }
                pubConfig();
            } else {
                Serial.print("FAIL");
                delay(5000);
            }
        } else {
            client.loop();
        }
    }
}
