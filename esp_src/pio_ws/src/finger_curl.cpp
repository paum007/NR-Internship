/*
Testing a sweep of the servos. The servos here were connected in a finger-like fashion 
(look at Pictures-and-videos: "Servos on top of each other finger arrangement.mp4" for a clearer representation):
DIP Servo
    |
PIP Servo
    |
MCP Servo
*/

#include <Arduino.h>
#include <ESP32Servo.h>

#define MCP_PIN 12
#define PIP_PIN 13
#define DIP_PIN 14

Servo servoMCP;
Servo servoPIP;
Servo servoDIP;


// Sweep a single servo smoothly from one angle to another.
void sweepTo(Servo &servo, int from, int to, int stepDelay) {
    if (from < to) {
        for (int a = from; a <= to; a++) {
            servo.write(a);
            delay(stepDelay);
        }
    } else {
        for (int a = from; a >= to; a--) {
            servo.write(a);
            delay(stepDelay);
        }
    }
}

void setup() {
    Serial.begin(115200);
    servoMCP.attach(MCP_PIN);
    servoPIP.attach(PIP_PIN);
    servoDIP.attach(DIP_PIN);

    // start all at 0
    servoMCP.write(0);
    servoPIP.write(0);
    servoDIP.write(0);
    delay(500);
}

void loop() {
    // --- one after another (sequential) ---
    sweepTo(servoMCP, 0, 15, 7);
    sweepTo(servoPIP, 0, 140, 7);
    sweepTo(servoDIP, 0, 45, 7);

    delay(1000);

    // sweep them back, in reverse order
    sweepTo(servoDIP, 45, 0, 7);
    sweepTo(servoPIP, 140, 0, 7);
    sweepTo(servoMCP, 15, 0, 7);

    delay(1000);
}