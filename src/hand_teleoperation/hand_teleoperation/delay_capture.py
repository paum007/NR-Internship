# This file reads the delay measurements sent by the ESP over the serial port (/dev/ttyUSB0),
# and logs every delay greater than 0 ms to delay_data.csv until stopped with Ctrl+C

import serial
import csv
import time

PORT = '/dev/ttyUSB0'
BAUD = 115200

ser = serial.Serial(PORT, BAUD, timeout=1)

with open('delay_data.csv', 'w', newline='') as f:
    writer = csv.writer(f)
    writer.writerow(['delay_ms'])

    try:
        while True:
            line = ser.readline().decode('utf_8', errors='ignore').strip()

            parts = line.split()
            try:
                delay = int(parts[2])
                if (delay>0):
                    writer.writerow([delay])
                    f.flush()
                    print(f'logged {delay} ms')

            except (IndexError, ValueError):
                pass

    except (KeyboardInterrupt):
        print('Stopped')
