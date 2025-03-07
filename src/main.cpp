#include "Arduino.h"
#include <WiFi.h>
#include <ESP32Servo.h>
#define LED_BUILTIN 2

const char* ssid = "";
const char* password = "";

void setup(){
    
    Serial.begin(921600);
    pinMode(LED_BUILTIN, OUTPUT);

    WiFi.begin(ssid, password);

    Serial.println("Starting");

}

bool isConnected = false;

void loop() {
    if (WiFi.status() == WL_CONNECTED && !isConnected) {
        Serial.println("Connected!");
        digitalWrite(LED_BUILTIN, HIGH);
        isConnected = true;
    }

    if (WiFi.status() != WL_CONNECTED) {
        //Serial.println(".");
        //digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
        delay(1000);
        isConnected = false;
    }

}