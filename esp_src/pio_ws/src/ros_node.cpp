#include <Arduino.h>
#include <WiFi.h>
#include <micro_ros_platfromio.h>

#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <geometry_msgs/msg/twist.h>


// --- Core micro-ROS objects (global: the executor references them every spin) ---
rcl_subscription_t subscriber;
geometry_msgs__msg__Twist mgs; // pre-allocated message struct (C won't alloc for you)

rclc_executor_t executor;
rclc_support_t support;
rcl_allocator_t allocator;
rcl_node_t node;

#define RCCHECK(fn) {rcl_ret_t temp_rc = fn; if ((temp_rc != RCL_RET_OK)){error_loop();}}
#define RCSOFTCHECK(fn) {rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){}}

// Error handle loop
void error_loop(){
    while(1) {
        // blink an LED or similar to see that init failed
        delay(100);
    }
}

void subscription_callback(const void *msgin){
    const geometry_msgs__msg__Twist *m = (const geometry_msgs__msg__Twist *)msgin;
    (void)m;

    // TODO: read the fields you care about, e.g. m->linear.x, m->angular.z
    // TODO: act on tehm (and later: ESP_NOW send to ESP-Will goes here)   
}

void setup(){
// --- WiFi transport to the agent ---
IPAddress agent_ip(172, 27, 92, 143);
size_t agent_port = 8888;

set_microros_wifi_transports("YOUR_SSID", "YOUR_PASSWORD", agent_ip, agent_port);
dealy(2000);

allocator = rcl_get_default_allocator();
RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));
RCCHECK(rclc_node_init_default(&node, "esp_henry_node", "", &support));

RCCHECK(rclc_subscription_init_default(
    &subscriber,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Twist),
    "cmd_vel"
));

RCCHECK(rclc_executor_init(&executor, &support.context, 1, &allocator));
RCCHECK(rclc_executor_add_subscription(
    &executor, &subscriber, &msg,
    &subscription_callback, ON_NEW_DATA));
}

void loop(){
    RCSOFTCHECK(rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100)));
}




