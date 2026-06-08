import math
import serial
from vpython import *

PORT = "COM3"
BAUD = 115200

ser = serial.Serial(PORT, BAUD, timeout=1)

scene = canvas(title="Wrist IMU", width=900, height=600, background=color.gray(0.1))

# --- build a hand shape out of primitives, then glue into one object ---
palm = box(length=2.4, height=0.4, width=2.0, color=vector(0.9, 0.75, 0.6))
fingers = [
    cylinder(pos=vector(1.2, 0, -0.7 + i*0.45), axis=vector(1.3, 0, 0), radius=0.16, color=vector(0.9, 0.75, 0.6))
    for i in range(4)
]

thumb = cylinder(pos=vector(0.6, 0, -1.1), axis=vector(0.7, 0, -0.6), radius=0.18, color=vector(0.9, 0.75, 0.6))
hand = compound([palm, thumb] + fingers)

while True:
    rate(60)
    line = ser.readline().decode("utf-8", errors="ignore").strip()

    if not line:
        continue

    try:
        pitch, roll, yaw = (float(v) for v in line.split(","))
    except ValueError:
        continue # skip malformed/partial lines (boot messages etc.)

    # map the three angles onto the hand's orientation
    hand.axis = vector(1, 0, 0) # reset each frame
    hand.up = vector(0, 1, 0)
    hand.rotate(angle=math.radians(pitch), axis=vector(0, 0, 1))
    hand.rotate(angle=math.radians(roll), axis=vector(1, 0, 0))
    hand.rotate(angle=math.radians(yaw), axis=vector(0, 1, 1))

