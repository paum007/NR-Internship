#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// WiFi ---
#include <WiFi.h>
#include "esp_wpa2.h"

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

// Must match ROS_DOMAIN_ID on the host. micro-ROS defaults to 0, so without this the
// ESP32 lands in a different DDS domain and never sees the publisher.
#define ROS_DOMAIN 42

// Network selection ----
// Uncomment to join a phone hotspot (plain WPA2) instead of the enterprise network.
// Comment it back out to go back to Modern_Networks.
#define USE_HOTSPOT
// #define NR_WIFI

#ifdef NR_WIFI
#define WIFI_SSID "National_Robotarium"
#define WIFI_PASSWORD "NatRobotarium309"
#elif defined(USE_HOTSPOT)
// Personal hotspot credentials ----
#define WIFI_SSID "pauma_hotspot"
#define WIFI_PASSWORD "23esu08arsom0"
#else
// Enterprise WiFi credentials ----
#define WIFI_SSID "Modern_Networks"
#define EAP_IDENTITY "Modern_Networks"
#define EAP_USERNAME "Robotarium-7"
#define EAP_PASSWORD "Dx4rHy+nGn"
#endif

// Servo settings
Adafruit_PWMServoDriver pca9685 = Adafruit_PWMServoDriver(0x40); // Create object to represent PCA9685 at default I2C address

#define SERVOMIN 80  // Minimum pulse count (0 deg)
#define SERVOMAX 600 // Maximum pulse count (180 deg)

// PCA9685 output channels (0-15), NOT ESP32 GPIO numbers
#define INDEX_CH 0
#define MIDDLE_CH 1
#define THUMB_CH 2

int targetINDEX = 0, targetMIDDLE = 0, targetTHUMB = 0;   // where ROS wants them
int currentINDEX = 0, currentMIDDLE = 0, currentTHUMB = 0; // where they are now

const int STEP = 2; // degrees moved per update  (smaller = smoother)
const unsigned long STEP_INTERVAL = 20; // ms between updates, matches the 50Hz frame (larger = slower)
unsigned long lastStep = 0;

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
// The host lands on a different subnet on a hotspot, so the agent address changes with it.
// Check the laptop's IP on the hotspot (`ip addr` / `hostname -I`) and update the hotspot line.

#ifdef NR_WIFI
IPAddress agent_ip(10, 47, 132, 183); // 1change depending on wifi
#elif defined(USE_HOTSPOT)
IPAddress agent_ip(172,20,10,11);
#else
IPAddress agent_ip(192, 168, 88, 198); // 192.168.88.198
#endif
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

    Serial.printf("[ROS] Received  INDEX: %.1f  MIDDLE: %.1f  THUMB: %.1f\n",
                  msg->index_mcp, msg->middle_mcp, msg->thumb_ip);

    // Clamp: a dropped/garbled frame must never push the servos past their travel
    targetINDEX = constrain((int)msg->index_mcp, 0, 180);
    targetMIDDLE = 180 - constrain((int)msg->middle_mcp, 0, 180);
    targetTHUMB = constrain((int)msg->thumb_ip, 0, 180);
}

void stepServo(uint8_t channel, int &current, int target, int step){

    if (current < target) {
        current = min(current + step, target);
    }
    else if (current > target) {
        current = max(current - step, target);
    }
    else {
        return; // already there, skip the I2C write
    }

    pca9685.setPWM(channel, 0, map(current, 0, 180, SERVOMIN, SERVOMAX));
}
// find the min and max from the current, because how will it know how to map without a range of values

void connectWiFi(){
#ifdef NR_WIFI
    Serial.print("Connecting to WiFi: ");
#elif defined(USE_HOTSPOT)
    Serial.print("Connecting to WiFi: ");
#else
    Serial.print("Connecting to enterprise WiFi: ");
#endif
    Serial.println(WIFI_SSID);

    WiFi.disconnect(true);
    WiFi.mode(WIFI_STA);

#ifdef NR_WIFI
    // Plain WPA2-PSK, no EAP setup needed
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
#elif defined(USE_HOTSPOT)
    // Plain WPA2-PSK, no EAP setup needed
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
#else
    // PEAP / MSCHAPv2, no anonymous indentity, no CA cert
    esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)EAP_IDENTITY, strlen(EAP_IDENTITY));
    esp_wifi_sta_wpa2_ent_set_username((uint8_t *)EAP_USERNAME, strlen(EAP_USERNAME));
    esp_wifi_sta_wpa2_ent_set_password((uint8_t *)EAP_PASSWORD, strlen(EAP_PASSWORD));
    esp_wifi_sta_wpa2_ent_enable();

    WiFi.begin(WIFI_SSID);
#endif

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
    Serial.printf("Resetted!! Reset reason: %d\n", esp_reset_reason());

    pinMode(LED_BUILTIN, OUTPUT);

    // PCA9685 board setup
    pca9685.begin();
    pca9685.setOscillatorFrequency(27000000); // must be set before setPWMFreq for an accurate frame rate
    pca9685.setPWMFreq(50); // set pwm frequency to 50Hz

    connectWiFi(); // join enterprise wifi or hotspot, see USE_HOTSPOT
    WiFi.setSleep(false);

    // WiFi is already associated by connectEnterpriseWiFi(). set_microros_wifi_transports()
    // would call WiFi.begin("", "") first, which fails with "SSID too long or missing!" —
    // enterprise credentials can't be passed as an ssid/pass pair. Install the UDP transport
    // directly instead; this is the rest of what that helper does.
    static struct micro_ros_agent_locator locator;
    locator.address = agent_ip;
    locator.port = agent_port;

    rmw_uros_set_custom_transport(
        false,
        (void *) &locator,
        platformio_transport_open,
        platformio_transport_close,
        platformio_transport_write,
        platformio_transport_read);

    delay(200);

    // QoS Profile ----
    rmw_qos_profile_t qos = rmw_qos_profile_default;

    qos.reliability = RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT;
    qos.durability = RMW_QOS_POLICY_DURABILITY_VOLATILE;
    qos.history = RMW_QOS_POLICY_HISTORY_KEEP_LAST;
    qos.depth = 1;
    
    allocator = rcl_get_default_allocator();

    // Set the DDS domain explicitly rather than using rclc_support_init(), which has no
    // domain parameter and would leave this node on domain 0.
    rcl_init_options_t init_options = rcl_get_zero_initialized_init_options();
    RCCHECK(rcl_init_options_init(&init_options, allocator));
    RCCHECK(rcl_init_options_set_domain_id(&init_options, ROS_DOMAIN));

    RCCHECK(rclc_support_init_with_options(&support, 0, NULL, &init_options, &allocator));
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

    // static char handedness_buf[20];
    // incoming_msg.handedness.data = handedness_buf;
    // incoming_msg.handedness.capacity = 20;
    // incoming_msg.handedness.size = 0;

    // static char frameid_buf[20];
    // incoming_msg.header.frame_id.data = frameid_buf;
    // incoming_msg.header.frame_id.capacity = 20;
    // incoming_msg.header.frame_id.size = 0;

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

    // Non-blocking: keeps the executor spinning while the servos ramp
    if (millis() - lastStep >= STEP_INTERVAL){
        lastStep = millis();

        stepServo(INDEX_CH, currentINDEX, targetINDEX, STEP);
        stepServo(MIDDLE_CH, currentMIDDLE, targetMIDDLE, STEP);
        stepServo(THUMB_CH, currentTHUMB, targetTHUMB, STEP);
    }
}
