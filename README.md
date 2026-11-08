# NR-Internship — Teleoperated Fin Ray Gripper

A research/internship project on a **soft Fin Ray–style gripper** for an xArm6, and on
**teleoperating it with hand tracking**.

The gripper's fingers are moulded from Dragonskin-30 and Vytaflex-60 and use the Fin Ray
effect: they bend around an object when pressed against it. The fingers are driven by
servos. The operator's hand is tracked, either by a webcam running **MediaPipe** or by a
**Meta Quest** headset. The finger joint angles are computed and filtered in **ROS 2**,
then streamed over Wi-Fi via **micro-ROS** to an ESP32. The ESP32 drives the gripper's
servos through a **PCA9685** PWM board.

## The gripper

- **Fingers:** cast in Dragon Skin and VytaFlex using 3D-printed moulds
  (`Finray mould v4`). Laser-cut and recycled-plastic sheets were also tried.
- **Mounting:** custom finger mounts (`finray-mount`, `flipped-finray-mount`), a servo
  arm pad and a gripper base, attached to the robot with an xArm6 coupler.
- **Files:** the CAD (Fusion 360 `.f3d`/`.f3z`, `.stl`, `.svg`/`.dxf`) is in
  [`CAD/`](CAD/). Photos of the moulding process and the finished gripper, plus demo
  videos, are in [`Pictures-and-videos/`](Pictures-and-videos/).

## Control system overview

```
 ┌──────────────┐  /camera/image_raw  ┌────────────────┐  /landmark_angles
 │ camera_ros   │ ──────────────────▶ │ mediapipe_node │ ─────────────────┐
 └──────────────┘    (sensor_msgs)    └────────────────┘   (HandAngles)   │
                                                                          ▼
 ┌──────────────┐  /teleop_hand_tracking/{left,right}/landmarks   ┌──────────────┐
 │ Meta Quest   │ ──────────────────────────────────────────────▶ │ filter_node  │
 │ (vuer bridge)│              (geometry_msgs/PoseArray)          └──────┬───────┘
 └──────────────┘                                                        │ /hand_angles
                                                                         │ (HandAngles)
                                          micro-ROS agent (UDP :8888)    ▼
                                   ┌──────────────────────────────────────────────┐
                                   │ ESP32 (finger_movement.cpp)                  │
                                   │  → rate-limited ramp → PCA9685 → servos      │
                                   └──────────────────────────────────────────────┘
```

- **`mediapipe_node`** runs the MediaPipe Hand Landmarker (live-stream mode) on camera
  frames. It computes joint angles from the 21 world landmarks and publishes
  `HandAngles` on `/landmark_angles` at 30 Hz. It also shows an annotated preview window.
- **`filter_node`** merges the two sources into one output. MediaPipe sends ready-made
  angles. The Quest sends 25 raw joint positions, so `filter_node` computes the angles
  itself. It then applies a per-source **deadband** to suppress tracking jitter
  (`threshold_mediapipe` = 2°, `threshold_quest` = 3°) and publishes on `/hand_angles`.
  The original source timestamp is kept so latency measurements stay honest.
- **`finger_movement.cpp`** (ESP32) subscribes to `hand_angles` with best-effort QoS on
  ROS domain **42**. It clamps each angle to 0–180° and ramps the servos towards the
  target at 2° per 20 ms, so a dropped or jumpy frame never slams a servo.

### `HandAngles` message

Defined in [`src/hand_teleoperation_interfaces/msg/HandAngles.msg`](src/hand_teleoperation_interfaces/msg/HandAngles.msg):

```
std_msgs/Header header
string handedness
float64 index_mcp
float64 middle_mcp
float64 ring_mcp
float64 thumb_ip
```

On the ESP32, `index_mcp` → PCA9685 channel 0, `middle_mcp` → channel 1 (inverted), and
`thumb_ip` → channel 2. `ring_mcp` is computed but not used. If more landmakrs need to be added, you can just give them a name and add them to the `HandAngles` message. 

## Hardware

| Component | Role |
|-----------|------|
| xArm6 | Robot arm the gripper mounts to |
| Fin Ray fingers + 3D-printed mounts | The gripper (see [`CAD/`](CAD/)) |
| MG996R-class hobby servos | Drive the gripper fingers |
| PCA9685 16-channel PWM board (I²C, `0x40`) | Generates 50 Hz servo signals |
| ESP32 (uPesy WROOM) | Runs the micro-ROS node that drives the servos |
| USB camera (`camera_ros`) | Input for MediaPipe hand tracking |
| Meta Quest + vuer bridge | Alternative hand-tracking input (25 joints per hand) |

See [`circuit_design.png`](circuit_design.png) for the ESP32 and servo-board wiring.

## Repository layout

```
CAD/                                  Fin Ray fingers, moulds, mounts, xArm6 coupler, laser files
Pictures-and-videos/                  Moulding process, gripper photos, servo/gripper demos
src/                                  ROS 2 workspace packages (colcon)
  hand_teleoperation/                 Python (ament_python) package
    hand_teleoperation/
      mediapipe_node.py               Camera → MediaPipe → HandAngles
      filter_node.py                  MediaPipe + Quest → deadband filter → /hand_angles
      filter.py                       Older filter draft (not installed as an entry point)
      delay_pub.py                    Publishes epoch-ms timestamps on /chatter (latency test)
      delay_capture.py                Logs the ESP32's serial delay readings to CSV
      delay_calculations.py           Mean/median/min/max/std of the logged delays
    launch/node.launch.py             camera_ros + mediapipe_node + filter_node
    data/                             hand_landmarker.task model, delay CSV and results
  hand_teleoperation_interfaces/      CMake package defining HandAngles.msg
esp_src/                              (COLCON_IGNORE, so colcon skips it)
  pio_ws/                             PlatformIO firmware workspace
    platformio.ini                    One build environment per firmware target
    extra_packages/                   Copy of hand_teleoperation_interfaces for micro-ROS
    src/
      finger_movement.cpp             MAIN: micro-ROS subscriber → PCA9685 servos
      delay_testing_ros.cpp           micro-ROS one-way latency test (/chatter)
      finger_curl.cpp                 Sweep test for three stacked servos (ESP32Servo)
      pca9685_testing.cpp             PCA9685 familiarisation sweep
      mac.cpp                         Print the board's Wi-Fi MAC address
Documents/                            Application, research write-up, presentations, reflections
Meeting notes/                        Supervision notes
VUER_HAND_TOPICS.md                   Quest hand-tracking topics and message format
research-notes.md                     References and Quest/vuer commands
errors.md                             Log of errors hit and how they were solved
to-do.md                              Running task list
```

## Getting started

### Prerequisites

- ROS 2 with `colcon` (the micro-ROS firmware targets **Jazzy**; the Quest/vuer
  container runs Humble)
- Python packages: `mediapipe`, `opencv-python`, `numpy`, `cv_bridge`. For the
  latency scripts, also `pyserial` and `pandas`.
- [`camera_ros`](https://github.com/christianrauch/camera_ros) for the webcam driver
- A micro-ROS agent (`micro_ros_agent`)
- [PlatformIO](https://platformio.org/) (CLI or the VS Code extension) for the firmware

### 1. Build and run the ROS 2 side

```bash
# from the repo root
colcon build --symlink-install
source install/setup.bash

export ROS_DOMAIN_ID=42          # must match ROS_DOMAIN in finger_movement.cpp

# camera + MediaPipe + filter
ros2 launch hand_teleoperation node.launch.py
```

To use the Quest instead, start the vuer bridge so that
`/teleop_hand_tracking/{left,right}/landmarks` is published (see
[`research-notes.md`](research-notes.md) and [`VUER_HAND_TOPICS.md`](VUER_HAND_TOPICS.md)).
`filter_node` picks it up automatically.

### 2. Start the micro-ROS agent

```bash
ros2 run micro_ros_agent micro_ros_agent udp4 --port 8888
```

### 3. Flash the ESP32 firmware

In [`finger_movement.cpp`](esp_src/pio_ws/src/finger_movement.cpp), set:

- the Wi-Fi network: choose between `NR_WIFI`, `USE_HOTSPOT`, or the default
  WPA2-Enterprise network, and fill in its credentials
- `agent_ip`: the laptop's IP address on that network (check with `hostname -I`)

Then build and upload:

```bash
cd esp_src/pio_ws
pio run -e finger_movement -t upload
pio device monitor -b 115200
```

Once the board prints `Clocks synched` and `[INFO] micro-ROS node ready.`, it logs every
`HandAngles` message it receives and the gripper's servos follow your fingers.

> The `upload_port` / `monitor_port` lines in `platformio.ini` are commented out so
> PlatformIO auto-detects the port. Set them if several boards are connected.

## Firmware environments

Each target is its own PlatformIO environment, selected with `-e`. The
`build_src_filter` in [`platformio.ini`](esp_src/pio_ws/platformio.ini) compiles exactly
one source file per environment.

| Environment | Source | Purpose |
|-------------|--------|---------|
| `finger_movement` | `finger_movement.cpp` | Main teleop node: `/hand_angles` → PCA9685 servos (micro-ROS, Jazzy) |
| `delay` | `delay_testing_ros.cpp` | Measures one-way host→ESP32 latency over micro-ROS |
| `finger_curl` | `finger_curl.cpp` | Sweeps three servos on GPIO 12/13/14 |
| `pca9685_testing` | `pca9685_testing.cpp` | Basic PCA9685 servo sweep |
| `mac` | `mac.cpp` | Prints the ESP32's MAC address |

## Latency measurement

1. Flash the `delay` environment. The ESP32 syncs its clock to the agent and subscribes
   to `/chatter`.
2. Run `ros2 run hand_teleoperation delay_pub`. It publishes the current epoch time
   (ms) once a second.
3. Run `delay_capture.py` to log the ESP32's `One-way delay: N ms` serial output to
   `delay_data.csv`.
4. Run `delay_calculations.py` to write summary statistics to `processed_data.txt`.

Latest results over micro-ROS on Wi-Fi ([`processed_data.txt`](src/hand_teleoperation/data/processed_data.txt)):

| Mean | Median | Min | Max | Std dev |
|------|--------|-----|-----|---------|
| 240 ms | 182 ms | 41 ms | 1121 ms | 180 ms |

## Status

- ✅ Fin Ray gripper prototype: moulded fingers, mounts and xArm6 coupler
- ✅ Webcam (MediaPipe) and Quest hand tracking → filtered joint angles in ROS 2
- ✅ ESP32 driving the gripper's servos over micro-ROS

See [`to-do.md`](to-do.md) for the running task list.

## License

[MIT](LICENSE) © 2026
