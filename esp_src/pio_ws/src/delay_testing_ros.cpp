#include <Arduino.h>

// WiFi ---
#include <WiFi.h>
#include "esp_wpa2.h"

// MicroROS imports ---
#include <stdio.h>
#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <rcl/error_handling.h>
#include <std_msgs/msg/string.h>
#include <micro_ros_platformio.h>
#include <rmw_microros/rmw_microros.h>

#define NODE_NAME "esp_henry"
#define SUBSCRIBER_TOPIC "chatter"

// Enterprise WiFi credentials ----
#define WIFI_SSID "Modern_Networks"
#define EAP_IDENTITY "Modern_Networks"
#define EAP_USERNAME "Robotarium-7"
#define EAP_PASSWORD "Dx4rHy+nGn"

// MicroROS Objects ----

#define RCCHECK(fn) {rcl_ret_t temp_rc = fn; if ((temp_rc != RCL_RET_OK)){error_loop();}}
#define RCSOFTCHECK(fn) {rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){}}

rcl_node_t node;
rcl_subscription_t subscriber;
rclc_executor_t executor;
rclc_support_t support;
rcl_allocator_t allocator;

std_msgs__msg__String incoming_msg;

// Agent ----
IPAddress agent_ip(192, 168, 88, 198); // 192.168.88.198
size_t agent_port = 8888;

// Buffer ----
#define BUFFER_SIZE 200
char incoming_buffer[BUFFER_SIZE];

// callback values ----
int64_t sent_ms;
int64_t now_ms;
int64_t delay_ms;


void error_loop(){
    while(1){
        Serial.println("[ERROR] Nothing is being received");
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
        delay(100);
    }
}

void subscription_callback(const void *msgin){
    const std_msgs__msg__String *msg = (const std_msgs__msg__String *)msgin;
    // all the timing logic here

    // Serial.print("[ROS] Received: ");
    Serial.println(msg->data.data);

        if (msg->data.data != NULL){
            sent_ms = atoll(msg->data.data); // the message payload IS the send-time in epoch miliseconds, as text
            now_ms = rmw_uros_epoch_millis(); // current time, in the AGENT's clock (valid because we synched)
            delay_ms = now_ms - sent_ms;
            
            Serial.print("One-way delay: ");
            Serial.print((long)delay_ms);
            Serial.println(" ms");
        }

        else{
            Serial.println("No data received");
        }

}

void connectEnterpriseWiFi(){
    Serial.println("Connecting to enterprise WiFi: ");
    Serial.println(WIFI_SSID);

    WiFi.disconnect(true);
    WiFi.mode(WIFI_STA);

    // PEAP / MSCHAPv2, no anonymous indentity, no CA cert
    esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)EAP_IDENTITY, strlen(EAP_IDENTITY));
    esp_wifi_sta_wpa2_ent_set_username((uint8_t *)EAP_USERNAME, strlen(EAP_USERNAME));
    esp_wifi_sta_wpa2_ent_set_password((uint8_t *)EAP_PASSWORD, strlen(EAP_PASSWORD));
    esp_wifi_sta_wpa2_ent_enable();

    WiFi.begin(WIFI_SSID);

    while (WiFi.status() != WL_CONNECTED){
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.print("Connected. IP: ");
    Serial.println(WiFi.localIP());

}

void setup(){
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);


    connectEnterpriseWiFi(); // join enterprise wifi

    set_microros_wifi_transports("", "", agent_ip, agent_port);
    delay(200);

    allocator = rcl_get_default_allocator();
    RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));
    RCCHECK(rclc_node_init_default(&node, NODE_NAME, "", &support));

    // Synching the clock to the agent
    while (!rmw_uros_epoch_synchronized()){
        RCSOFTCHECK(rmw_uros_sync_session(1000));
        delay(500);
    }

    Serial.println("Clocks synched");

    RCCHECK(rclc_subscription_init_default(
        &subscriber,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, String), SUBSCRIBER_TOPIC));

    // giving the message a buffer to receive into ----
    incoming_msg.data.data = incoming_buffer;
    incoming_msg.data.capacity = BUFFER_SIZE;
    incoming_msg.data.size = 0;

    RCCHECK(rclc_executor_init(&executor, &support.context, 1, &allocator));
    RCCHECK(rclc_executor_add_subscription(
        &executor,
        &subscriber,
        &incoming_msg,
        &subscription_callback,
        ON_NEW_DATA));

    Serial.println("[INFO] micro-ROS node ready.");    

}

void loop(){
    RCSOFTCHECK(rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100)));
    delay(10);
}
