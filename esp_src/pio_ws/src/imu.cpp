#include <Arduino.h>
#include <Wire.h>

const int MPU_ADDR = 0x68;

int16_t accelerometer_x, accelerometer_y, accelerometer_z, gyro_x, gyro_y, gyro_z, temperature;

float pitch = 0, roll = 0, yaw = 0;
float gyroXoffset = 0, gyroYoffset = 0, gyroZoffset = 0;
unsigned long lastMicros = 0;

void readRaw(){
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom((uint8_t)MPU_ADDR, (uint8_t)14, true); // request a total of 14 registers

    accelerometer_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
    accelerometer_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
    accelerometer_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
    temperature = Wire.read()<<8 | Wire.read();
    gyro_x = Wire.read()<<8 | Wire.read();
    gyro_y = Wire.read()<<8 | Wire.read();
    gyro_z = Wire.read()<<8 | Wire.read();

}

void setup(){
    Serial.begin(115200);
    Wire.begin(21, 22);
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x6B); // PWR_MGMT_1 register
    Wire.write(0); // wake up the MPU
    Wire.endTransmission(true);

    // --- gyro bias calibration: hold the IMU STILL during this ---
    long sx = 0, sy = 0, sz = 0;
    for (int i=0; i<1000; i++){
        readRaw(); 
        sx += gyro_x;
        sy += gyro_y;
        sz += gyro_z;
        delay(2);

        gyroXoffset = sx/1000.0;
        gyroYoffset = sy/1000.0;
        gyroZoffset = sz/1000.0;

        lastMicros = micros();
    }
}

void loop(){   

    readRaw();

    // dt = real elapsed time, needed to integrate the gyro correctly
    unsigned long now = micros();
    float dt = (now-lastMicros) / 1000000.0;

    // accel -> absolute tilt angles (the drift-free(ish) reference)
    float accPitch = atan2(accelerometer_y, accelerometer_z) * 180.0 / PI;
    float accRoll = atan2(-accelerometer_x, sqrt(accelerometer_y*(float)accelerometer_y + accelerometer_z*(float)accelerometer_z))*180.0/PI;

    // gyro -> rotation rate in deg/s (subtract bias, /131 for +-250 range)
    float gyroPitchRate = (gyro_x - gyroXoffset) / 131.0;
    float gyroRollRate = (gyro_y - gyroYoffset) / 131.0;
    float gyroYawRate = (gyro_z - gyroZoffset) / 131.0;

    // complementary filter: trust gyro short-term, accel long-term
    pitch = 0.96*(pitch + gyroPitchRate * dt) + 0.04*accPitch;
    roll = 0.96*(roll + gyroRollRate * dt) + 0.04 * accRoll;
    yaw += gyroYawRate*dt; // yaw has NO accel reference -> WILL drift
    
    // the contract: three numbers, comma-separated, one line
    Serial.print(pitch); Serial.print(",");
    Serial.print(roll);  Serial.print(",");
    Serial.println(yaw);

    delay(20);  // ~50 Hz


    // delay
    // delay(1000); // WARING: This delay is only to make the values readable. Change to 20 for the testing.


}