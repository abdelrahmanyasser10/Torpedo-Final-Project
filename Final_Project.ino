#include "main.h"

void setup() {

  // Setup Serial Monitor for testing
  Serial.begin(115200);

  PS3_Controller_Setup();
  communication_setup();
  selection_mode_setup();
  dcMotors_Pins_Setup();
  dcMotors_Control_Setup();
  attach_Servo_Pin();
  Servo_Control_Setup();
  IR_Pin_Setup();
  encoder_setup();
  IMU_setup();


  // Print to Serial Monitor
  Serial.println("Ready.");

}

void loop() {
  
  if (!Ps3.isConnected())
  {
    Serial.println("Not Connected");
  }

  if(flag1 == 1)
  {
    Line_Following_IR();
  }

  if(flag2 == 1)
  {
    Line_Following_CV();
  }

  delay(2000);

}
