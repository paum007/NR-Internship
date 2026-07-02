#include <Arduino.h>

// WiFi ---
#include <WiFi.h>
#include "esp_wpa2.h"

// Servo imports ---
#include <ESP32Servo.h>

// MicroROS imports ---
#include <stdio.h>
#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <rcl/error_handling.h>
#include <micro_ros_platformio.h>
#include <rmw_microros/rmw_microros.h>
#include <hand_teleoperation_interfaces/msg/hand_angles.h>

#define NODE_NAME "esp_henry"
#define SUBSCRIBER_TOPIC "hand_angles"

// Enterprise WiFi credentials ----
#define WIFI_SSID "Modern_Networks"
#define EAP_IDENTITY "Modern_Networks"
#define EAP_USERNAME "Robotarium-7"
#define EAP_PASSWORD "Dx4rHy+nGn"

#define INDEX_MCP_PIN 12
#define INDEX_PIP_PIN 13
#define INDEX_DIP_PIN 14

Servo servoIndexMCP;
Servo servoIndexPIP;
Servo servoIndexDIP;

// MicroROS Objects ----

#define RCCHECK(fn) {rcl_ret_t temp_rc = fn; if ((temp_rc != RCL_RET_OK)){error_loop();}}
#define RCSOFTCHECK(fn) {rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){}}

rcl_node_t node;
rcl_subscription_t subscriber;
rclc_executor_t executor;
rclc_support_t support;
rcl_allocator_t allocator;

hand_teleoperation_interfaces__msg__HandAngles incoming_msg;

// Agent ----
IPAddress agent_ip(192, 168, 88, 198); // 192.168.88.198
size_t agent_port = 8888;

void error_loop(){
    while(1){
        Serial.println("[ERROR] Nothing is being received");
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
        delay(100);
    }
}

void subscription_callback(const void *msgin){
    const hand_teleoperation_interfaces__msg__HandAngles *msg = (const hand_teleoperation_interfaces__msg__HandAngles *)msgin;

    Serial.print("[ROS] Received: "); Serial.println(msg->index_mcp);
    servoIndexMCP.write((int)msg->index_mcp);
    servoIndexPIP.write((int)msg->index_pip);
    servoIndexDIP.write((int)msg->index_dip);

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

    // attaching the servos
    servoIndexMCP.attach(INDEX_MCP_PIN);
    servoIndexPIP.attach(INDEX_PIP_PIN);
    servoIndexDIP.attach(INDEX_DIP_PIN);

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
        ROSIDL_GET_MSG_TYPE_SUPPORT(hand_teleoperation_interfaces, msg, HandAngles), SUBSCRIBER_TOPIC));

    static char handedness_buf[20];
    incoming_msg.handedness.data = handedness_buf;
    incoming_msg.handedness.capacity = 20;
    incoming_msg.handedness.size = 0;

    static char frameid_buf[20];
    incoming_msg.header.frame_id.data = frameid_buf;
    incoming_msg.header.frame_id.capacity = 20;
    incoming_msg.header.frame_id.size = 0;

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
