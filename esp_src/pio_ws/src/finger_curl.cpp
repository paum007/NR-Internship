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

// Make a function that returns the angle data from the computer vision and make it so that data goes into the sweepTo function
// I might not even need this to process the angles if I already process the angle data and put it as a publisher, that angle can go into the sweepTo directly.

// int angle(/*The camera vision stuff will go in here I assume or this will be the data collected from a publisher*/){

// }

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