#include "main.h"


void IMU_setup()
{
  Wire.begin();
  Serial.println("Initialize MPU6050");

  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
}

float get_angle()
{
  float yaw;
  
  Vector rawGyro = mpu.readRawGyro();
  Vector normGyro = mpu.readNormalizeGyro();

  yaw = normGyro.ZAxis;

  Serial.print("Yaw: ");
  Serial.println(yaw);
  return yaw;
}