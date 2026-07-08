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
#include <rmw/qos_profiles.h>
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

int targetMCP = 0, targetPIP = 0, targetDIP = 0;   // where ROS wants them
int currentMCP = 0, currentPIP = 0, currentDIP = 0; // where they are now

const int STEP = 2; // degrees moved per update  (smaller = smoother)
const int STEP_DELAY = 0; // ms between updates (larger  = slower)

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

    Serial.printf("[ROS] Received  MCP: %.1f  PIP: %.1f  DIP: %.1f\n",
                  msg->index_mcp, msg->index_pip, msg->index_dip);
    targetMCP = (int)msg->index_mcp;
    targetPIP = (int)msg->index_pip;
    targetDIP = (int)msg->index_dip;
}

void stepServo(Servo &s, int &current, int target, int step){
    if (current < target) {
        current = min(current + step, target);
    }
    else if (current > target) {
        current = max(current - step, target);
    }
    s.write(current);   // always push the current position to the servo
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

    // QoS Profile ----
    rmw_qos_profile_t qos = rmw_qos_profile_default;

    qos.reliability = RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT;
    qos.durability = RMW_QOS_POLICY_DURABILITY_VOLATILE;
    qos.history = RMW_QOS_POLICY_HISTORY_KEEP_LAST;
    qos.depth = 1;

    // attaching the servos
    servoIndexMCP.attach(INDEX_MCP_PIN);
    servoIndexPIP.attach(INDEX_PIP_PIN);
    servoIndexDIP.attach(INDEX_DIP_PIN);

    // reset to 0 once on startup
    servoIndexMCP.write(0);
    servoIndexPIP.write(0);
    servoIndexDIP.write(0);
    delay(500);

    allocator = rcl_get_default_allocator();
    RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));
    RCCHECK(rclc_node_init_default(&node, NODE_NAME, "", &support));

    // Synching the clock to the agent
    while (!rmw_uros_epoch_synchronized()){
        RCSOFTCHECK(rmw_uros_sync_session(1000));
        delay(500);
    }

    Serial.println("Clocks synched");

    RCCHECK(rclc_subscription_init(
        &subscriber,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(hand_teleoperation_interfaces, msg, HandAngles), SUBSCRIBER_TOPIC, &qos));

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
    RCSOFTCHECK(rclc_executor_spin_some(&executor, RCL_MS_TO_NS(10)));

    stepServo(servoIndexMCP, currentMCP, targetMCP, STEP);
    stepServo(servoIndexPIP, currentPIP, targetPIP, STEP);
    stepServo(servoIndexDIP, currentDIP, targetDIP, STEP);

    delay(STEP_DELAY);
}
