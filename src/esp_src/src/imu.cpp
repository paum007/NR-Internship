#include <Arduino.h>
#include <Wire.h>

const int MPU_ADDR = 0x68;

int16_t accelerometer_x, accelerometer_y, accelerometer_z;
int16_t gyro_x, gyro_y, gyro_z;
int16_t temperature;

char tmp_str[8];

char* convert_int16_to_str(int16_t i){
    sprintf(tmp_str, "%6d", i);
    return tmp_str;
}

void setup(){
    Serial.begin(115200);
    Wire.begin(21, 22);
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x6B); // PWR_MGMT_1 register
    Wire.write(0);
    Wire.endTransmission(true);
}

void loop(){
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
    Wire.endTransmission(false);
    Wire.requestFrom((uint8_t)MPU_ADDR, (uint8_t)14, true); // request a total of 14 registers

    accelerometer_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
    accelerometer_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
    accelerometer_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
    temperature = Wire.read()<<8 | Wire.read();
    gyro_x = Wire.read()<<8 | Wire.read();
    gyro_y = Wire.read()<<8 | Wire.read();
    gyro_z = Wire.read()<<8 | Wire.read();

     // print out data
    Serial.print("aX = "); Serial.print(convert_int16_to_str(accelerometer_x));
    Serial.print(" | aY = "); Serial.print(convert_int16_to_str(accelerometer_y));
    Serial.print(" | aZ = "); Serial.print(convert_int16_to_str(accelerometer_z));
    // the following equation was taken from the documentation [MPU-6000/MPU-6050 Register Map and Description, p.30]
    Serial.print(" | tmp = "); Serial.print(temperature/340.00+36.53);
    Serial.print(" | gX = "); Serial.print(convert_int16_to_str(gyro_x));
    Serial.print(" | gY = "); Serial.print(convert_int16_to_str(gyro_y));
    Serial.print(" | gZ = "); Serial.print(convert_int16_to_str(gyro_z));
    Serial.println();


    // delay
    delay(1000); // WARING: This delay is only to make the values readable. Change to 20 for the testing.


}