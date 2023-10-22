#include "main.h"

void setup() {
  // put your setup code here, to run once:

  // Setting Serial
  Serial.begin(115200);

  // Start Communication
  communication_setup();
  
  // Motors Setup
  motorDriver_setup();

  //Servo Setup
  servo_setup();

  // IR Sensor Setup
  IR_setup();

  // ISR Setup
  ISR_Setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(flag)
    keyboard_control();
  else
    Line_Following_IR();
}
