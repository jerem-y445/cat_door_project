#include "Arduino.h"
#include <WiFiMulti.h>
#include <WiFi.h>
#define LED_BUILTIN 2

const char* ssid = "casa";
const char* password = "91-plum-1724";

WiFiMulti wifimulti;

void setup(){
    Serial.begin(921600);
    pinMode(LED_BUILTIN, OUTPUT);

    WiFi.begin(ssid, password);

    Serial.println("Starting");

    /*wifimulti.addAP(ssid, password);
    
    while (wifimulti.run() != WL_CONNECTED) {
        delay(100);
    }

    Serial.println("Connected!");*/
    
}

bool isConnected = false;

void loop() {
    if (WiFi.status() == WL_CONNECTED && !isConnected) {
        Serial.println("Connected!");
        digitalWrite(LED_BUILTIN, HIGH);
        isConnected = true;
    }

    if (WiFi.status() != WL_CONNECTED) {
        Serial.println(".");
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
        delay(1000);
        isConnected = false;
    }

    //digitalWrite(LED_BUILTIN, WiFi.status() == WL_CONNECTED);

}