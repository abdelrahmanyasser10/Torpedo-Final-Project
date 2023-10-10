#include "main.h"

void dcMotors_Control()
{
    if(flag == 0)
    {
         // Get Joystick value
      leftX = (Ps3.data.analog.stick.lx);
      leftY = (Ps3.data.analog.stick.ly);

      //Determine direction from Y axis position
      if (leftY < 0) {
        // Direction is forward
        motorDir = true;
      } else {
        // Direction is reverse
        motorDir = false;
      }

      // Convert joystick values to positive 0 - 255
      int speedX = (abs(leftX) * 2);
      int speedY = (abs(leftY) * 2);

      // Factor in the X axis value to determine motor speeds (assume Motor A is Left motor going forward)
      if (leftX < -10) {
        // Motor B faster than Motor A
        motorAPWM = speedY - speedX;
        motorBPWM = speedY + speedX;

      } else if (leftX > 10) {
        // Motor A faster than Motor B
        motorAPWM = speedY + speedX;
        motorBPWM = speedY - speedX;

      } else {
        // Control is in middle, both motors same speed
        motorAPWM = 0;
        motorBPWM = 0;
      }

      // Ensure that speed values remain in range of 0 - 255
      motorAPWM = constrain(motorAPWM, 0, 255);
      motorBPWM = constrain(motorBPWM, 0, 255);

      // Drive the motors
      moveMotors(motorAPWM, motorBPWM, motorDir);

      // Print to Serial Monitor
      Serial.print("Motor A = ");
      Serial.print(motorAPWM);
      Serial.print(" - Motor B = ");
      Serial.print(motorBPWM);

    }
}

// Motor movement function
void moveMotors(int mtrAspeed, int mtrBspeed, bool mtrdir) {
  // Set direction pins
  if (!mtrdir) {
    // Move in reverse
    digitalWrite(AIN1_PIN, HIGH);
    digitalWrite(AIN2_PIN, LOW);
    digitalWrite(BIN1_PIN, HIGH);
    digitalWrite(BIN2_PIN, LOW);

  } else {
    // Move Forward
    digitalWrite(AIN1_PIN, LOW);
    digitalWrite(AIN2_PIN, HIGH);
    digitalWrite(BIN1_PIN, LOW);
    digitalWrite(BIN2_PIN, HIGH);
  }

  // Drive motors with PWM
  ledcWrite(motorAChannel, mtrAspeed);
  ledcWrite(motorBChannel, mtrBspeed);
}

void dcMotors_Pins_Setup()
{
  // Set motor controller pins as outputs
  pinMode(PWMA_PIN, OUTPUT);
  pinMode(PWMB_PIN, OUTPUT);
  pinMode(AIN1_PIN, OUTPUT);
  pinMode(AIN2_PIN, OUTPUT);
  pinMode(BIN1_PIN, OUTPUT);
  pinMode(BIN2_PIN, OUTPUT);

}

void dcMotors_Control_Setup()
{
  // Define Callback Function
  Ps3.attach(dcMotors_Control);

  // Set channel Parameters for each motor
  ledcSetup(motorAChannel, motorFreq, motorResolution);
  ledcSetup(motorBChannel, motorFreq, motorResolution);

  // Attach Motor PWM pins to corresponding channels
  ledcAttachPin(PWMA_PIN, motorAChannel);
  ledcAttachPin(PWMB_PIN, motorBChannel);

}