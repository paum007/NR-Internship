// This file finds the MAC Address of the ESP32

#include <Arduino.h>
#include <WiFi.h>

void setup(){
    Serial.begin(115200);
    delay(500);
    WiFi.mode(WIFI_STA);
    Serial.print("Receiver MAC: ");
    Serial.println(WiFi.macAddress());
}

void loop(){}