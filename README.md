# NR-Internship — Embodied Teleoperation for Human-like Robotic Manipulation

A research/internship project on **bilateral teleoperation with haptic feedback** for
human-like robotic manipulation. A sensorised glove worn by an operator drives a
robotic hand in real time, and contact detected at the robot's fingertips is fed back
to the operator's hand — closing the loop so the human "feels" what the robot touches.

> Working names used throughout the code and notes:
> - **Will** — the *sensorised glove* (the operator-side input device)
> - **Henry** — the *robotic hand* (the follower that mirrors the operator's motion)

## Concept

The operator commands motion; their finger position is the input. The two directions of
the loop are deliberately **asymmetric**:

- **Forward (command):** Will's finger bend → calibrated mapping → Henry's servo target.
  All the angle translation lives here, because the glove's and the hand's kinematics differ.
- **Return (feedback):** Henry's fingertip force → a single *contact / no-contact* bit →
  a brake on Will locks the operator's finger at its current position. No angle translation
  at all.

Because the operator is the only thing moving the fingers, locking the glove at the moment
of contact naturally keeps Henry's pose matched to Will's — no encoders or closed-loop
position control on the glove are required. Calibration happens between the glove's flex
sensors and Henry's servos.

## Hardware

| Component | Role |
|-----------|------|
| ESP32 (uPesy WROOM) ×N | Microcontrollers on both glove and hand |
| Flex / potentiometer sensors | Read operator finger bend on the glove |
| Hobby servos (via ESP32Servo) | Actuate the robotic hand's joints (MCP / PIP / DIP) |
| LIS3MDL magnetometer | Magnetic-field-based tactile / fingertip sensing |
| MPU-6050 IMU | Orientation (accelerometer + gyro, complementary filter) |
| 3D-printed parts | Custom hand + fingertip (see [`CAD/`](CAD/)) |

Communication between the glove and hand uses **ESP-NOW** (peer-to-peer Wi-Fi, no router).
A separate **micro-ROS** path bridges the system to a ROS 2 (Humble) host.

## Repository layout

```
esp_src/pio_ws/          PlatformIO workspace (firmware)
  platformio.ini         Build environments (one per firmware target)
  src/
    transmitter.cpp      Glove side: read pots, send over ESP-NOW
    receiver.cpp         Hand side: receive packets, drive servos, link failsafe
    finger_curl.cpp      Standalone 3-servo finger sweep (MCP/PIP/DIP) demo
    magnetometer.cpp     LIS3MDL magnetometer read demo
    imu.cpp              MPU-6050 read + complementary filter (pitch/roll/yaw)
    mac.cpp              Utility: print the board's Wi-Fi MAC address
    ros_node.cpp         micro-ROS node subscribing to /turtle1/cmd_vel
CAD/                     3D-printable models (e.g. Fingertip1.stl)
research-notes.md        Design decisions, references, datasheets
to-do.md                 Running task list
Meeting notes/           Supervision / meeting notes
```

## Firmware environments

Each target is its own PlatformIO environment, selected with `-e`. The `build_src_filter`
in [`platformio.ini`](esp_src/pio_ws/platformio.ini) compiles exactly one source file per
environment.

| Environment | Source | Purpose |
|-------------|--------|---------|
| `transmitter` | `transmitter.cpp` | Glove: read two pots, smooth, send over ESP-NOW |
| `receiver` | `receiver.cpp` | Hand: receive pot values, map to servo angles, 500 ms link-loss failsafe |
| `finger_curl` | `finger_curl.cpp` | Sweep a 3-joint finger through a curl motion |
| `magneto` | `magnetometer.cpp` | Read the LIS3MDL magnetometer |
| `microros` | `ros_node.cpp` | micro-ROS node over Wi-Fi to a ROS 2 agent |
| `mac` | `mac.cpp` | Print the ESP32's MAC address |

## Getting started

### Prerequisites

- [PlatformIO](https://platformio.org/) (CLI or the VS Code extension)
- An ESP32 dev board (configured for `upesy_wroom`)

### Build & upload

```bash
cd esp_src/pio_ws

# Build a target
pio run -e receiver

# Upload to a connected board
pio run -e transmitter -t upload

# Open the serial monitor (115200 baud)
pio device monitor -b 115200
```

> The `upload_port` / `monitor_port` lines in `platformio.ini` are commented out so
> PlatformIO auto-detects the port. Set them (e.g. `COM4`) if you have several boards
> connected at once.

### Pairing the glove and hand (ESP-NOW)

ESP-NOW addresses peers by MAC, so the transmitter needs to know the receiver's address:

1. Flash `mac` to the **receiver** board and read its MAC from the serial monitor.
2. Put that address in `receiverMAC[]` in [`transmitter.cpp`](esp_src/pio_ws/src/transmitter.cpp).
3. Flash `transmitter` to the glove board and `receiver` to the hand board.

The receiver maps incoming 0–4095 ADC values to 0–180° servo angles and holds its last
position if it stops hearing packets for 500 ms.

### micro-ROS

The `microros` environment builds a node that connects to a ROS 2 (Humble) agent over
Wi-Fi and subscribes to `/turtle1/cmd_vel`. Set your Wi-Fi SSID/password and the agent's
IP/port in [`ros_node.cpp`](esp_src/pio_ws/src/ros_node.cpp), then run a micro-ROS agent
on the host, e.g.:

```bash
ros2 run micro_ros_agent micro_ros_agent udp4 --port 8888
```

## Status

Early prototyping. Current focus is proving the haptic loop end-to-end with a **single
finger** before committing to a full hand build. See [`to-do.md`](to-do.md) and
[`research-notes.md`](research-notes.md) for the latest direction and open questions.

## License

[MIT](LICENSE) © 2026
