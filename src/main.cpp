#include "Arduino.h"
#include <WiFi.h>
#include <ESP32Servo.h>
#define LED_BUILTIN 2

const char* ssid = "<insert wifi name here>";
const char* password = "<insert wifi password here>";

Servo servo1, servo2;
int pos = 0;
int servoPin1 = 18;
int servoPin2 = 12;

void setup(){
    
    /*Serial.begin(921600);
    pinMode(LED_BUILTIN, OUTPUT);

    WiFi.begin(ssid, password);

    Serial.println("Starting");*/

    // Servo timer allocations
    ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	servo1.setPeriodHertz(50);
	servo1.attach(servoPin1, 500, 2400);
    servo2.setPeriodHertz(50);
	servo2.attach(servoPin2, 500, 2400);

}

//bool isConnected = false;
bool isOutside = false;

void loop() {
    /*if (WiFi.status() == WL_CONNECTED && !isConnected) {
        Serial.println("Connected!");
        digitalWrite(LED_BUILTIN, HIGH);
        isConnected = true;
    }

    if (WiFi.status() != WL_CONNECTED) {
        //Serial.println(".");
        //digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
        //delay(1000);
        isConnected = false;
    }*/
    
    while(oneSweep < 1) {
        for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
            // in steps of 1 degree
            myServo.write(pos);    // tell servo to go to position in variable 'pos'
            delay(15);             // waits 15ms for the servo to reach the position
        }
        for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
            myServo.write(pos);    // tell servo to go to position in variable 'pos'
            delay(15);
        }
        oneSweep++;
    }

}