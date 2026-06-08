#include <Arduino.h>
#include <WiFi.h>       // needed to put the radio into Wi-Fi mode (ESP-NOW rides on the Wi-Fi hardware)
#include <esp_now.h>    // the ESP-NOW peer-to-peer protocol API
#include <ESP32Servo.h> // servo PWM control
// #include <esp_wifi.h>

// esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE);

#define SERVO_PIN1 13    // GPIO the servo signal wire is connected to
#define SERVO_PIN2 12

// The "packet" layout. This struct MUST be identical on the transmitter and
// receiver — same fields, same order, same types — or the bytes won't line up.
typedef struct{
    int potValue1;       // the potentiometer reading the transmitter sends (0..4095)
    int potValue2;       // the potentiometer reading the transmitter sends (0..4095)
} Packet;

Packet packet;          // a reusable buffer the incoming bytes get copied into
Servo myServo1;
Servo myServo2;

// Shared between the radio callback and loop(). Marked volatile because the
// callback runs in a different context than loop(), so the compiler must not
// cache these in registers — it has to re-read them from memory every time.
volatile unsigned long lastPacketMs = 0; // millis() timestamp of the last packet we heard
volatile int latestValue1 = 0;            // most recent potValue received
volatile int latestValue2 = 0;            // most recent potValue received
volatile bool gotNew = false;            // flag: a fresh packet arrived since loop() last looked
bool linkAlive;                          // true while we're still hearing from the transmitter

// Called AUTOMATICALLY by ESP-NOW whenever a packet arrives — you never call
// this yourself. `mac` = sender's address, `data` = raw bytes, `len` = byte count.
void onReceive(const uint8_t *mac, const uint8_t *data, int len){
    if (len == sizeof(Packet)){          // sanity check: only accept packets that are exactly our struct's size
        memcpy(&packet, data, sizeof(packet)); // copy the raw bytes into our struct
        latestValue1 = packet.potValue1;   // pull the field out
        latestValue2 = packet.potValue2;   // pull the field out
        lastPacketMs = millis();         // remember when we last heard something
        gotNew = true;                   // tell loop() there's fresh data
    }
}

void setup(){
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);                 // station mode — required before ESP-NOW will init

    myServo1.attach(SERVO_PIN1);
    myServo2.attach(SERVO_PIN2);

    if (esp_now_init() != ESP_OK){       // bring up the ESP-NOW stack; bail if it fails
        Serial.println("ESP-NOW init failed");
        return;
    }

    esp_now_register_recv_cb(onReceive); // register our function as the "packet arrived" handler
    Serial.println("Receiver ready, waiting for packets");
}

void loop(){
    // If we haven't heard a packet in the last 500ms, consider the link dead.
    linkAlive = (millis() - lastPacketMs) < 500;

    if (linkAlive){
        // Rescale the 0..4095 ADC range to a 0..180 degree servo angle.
        int angle1 = map(latestValue1, 0, 4095, 0, 180);
        myServo1.write(angle1);

        int angle2 = map(latestValue2, 0, 4095, 0, 180);
        myServo2.write(angle2);

        if (gotNew){                     // only log when something actually changed
            Serial.printf("Servo 1 got: %4d -> Angle: %3d\n", latestValue1, angle1);
            Serial.printf("Servo 2 got: %4d -> Angle: %3d\n", latestValue2, angle2);
            gotNew = false;              // clear the flag until the next packet
        }
    }

    else{
    // FAILSAFE: no data for 500ms. Hold last position (do nothing),
    // or uncomment to recentre:
    // myServo.write(90);

        Serial.println("** link lost - no packets **");
        delay(200); // don't spam the log
    }

    delay(20); // ~50 Hz loop; keeps the servo updates smooth without flooding

}
