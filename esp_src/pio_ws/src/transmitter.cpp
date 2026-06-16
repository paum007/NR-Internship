#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
// #include <esp_wifi.h>

#define POT_PIN1 34
#define POT_PIN2 35

uint8_t receiverMAC[] = {0xC8, 0xF0, 0x9E, 0x4F, 0x10, 0x7C};

typedef struct{
    int potValue1;
    int potValue2;
} Packet;

Packet packet;
float smoothed_pot1 = 0;
float smoothed_pot2 = 0;
bool peerOk = false;
int raw_pot1;
int raw_pot2;

// esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE);

void onSent(const uint8_t *mac, esp_now_send_status_t status){
    if (status != ESP_NOW_SEND_SUCCESS){
        Serial.println(" [send failed - receiver not reachable?] ");
    }
}

void setup(){
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);

    if (esp_now_init() != ESP_OK){
        Serial.println("ESP-NOW init failed");
        return;
    }

    esp_now_register_send_cb(onSent);

    esp_now_peer_info_t peer = {};
    memcpy(peer.peer_addr, receiverMAC, 6);
    peer.channel = 0;
    peer.encrypt = false;

    if (esp_now_add_peer(&peer) == ESP_OK){
        peerOk = true;
    }

    else{
        Serial.println("Failed to peer");
    }
}

void loop(){
    raw_pot1 = analogRead(POT_PIN1);
    smoothed_pot1 = smoothed_pot1*0.8 + raw_pot1*0.2;

    raw_pot2 = analogRead(POT_PIN2);
    smoothed_pot2 = smoothed_pot2*0.8 + raw_pot2*0.2;

    packet.potValue1 = (int)smoothed_pot1;
    packet.potValue2 = (int)smoothed_pot2;

    if (peerOk){
        esp_now_send(receiverMAC, (uint8_t *)&packet, sizeof(packet));
    }

    Serial.printf("Pot raw1: %4d smoothed: %4d\n", raw_pot1, packet.potValue1);
    Serial.printf("Pot raw2: %4d smoothed: %4d\n", raw_pot2, packet.potValue2);
    delay(20);
}
