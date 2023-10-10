#include "main.h"


void Line_Following_IR()
{
    Serial.println(digitalRead(leftIR));
    Serial.println(digitalRead(rightIR));

    if(digitalRead(leftIR)==0 && digitalRead(rightIR)==0)
      moveForward(100);
    else if(digitalRead(leftIR)==0 && !digitalRead(rightIR)==0)
      turnLeft(100);
    else if(!digitalRead(leftIR)==0 && digitalRead(rightIR)==0)
      turnRight(100);
    else if(!digitalRead(leftIR)==0 && !digitalRead(rightIR)==0)
    {
      Stop();
    }
  
}

void moveForward(int speed)
{
  Serial.println("Moving Forward");
  digitalWrite(AIN1_PIN, HIGH);
  digitalWrite(AIN2_PIN, LOW);
  digitalWrite(BIN1_PIN, HIGH);
  digitalWrite(BIN2_PIN, LOW);

  analogWrite(PWMA_PIN, speed);
  analogWrite(PWMB_PIN, speed);
}

void moveBackward(int speed)
{
  Serial.println("Moving backward");
  digitalWrite(AIN1_PIN, LOW);
  digitalWrite(AIN2_PIN, HIGH);
  digitalWrite(BIN1_PIN, LOW);
  digitalWrite(BIN2_PIN, HIGH);

  analogWrite(PWMA_PIN, speed);
  analogWrite(PWMB_PIN, speed);
}

void turnRight(int speed)
{
  Serial.println("Turning right");
  digitalWrite(AIN1_PIN, LOW);
  digitalWrite(AIN2_PIN, HIGH);
  digitalWrite(BIN1_PIN, HIGH);
  digitalWrite(BIN2_PIN, LOW);

  analogWrite(PWMA_PIN, speed);
  analogWrite(PWMB_PIN, speed);
}

void turnLeft(int speed)
{
  Serial.println("Turning left");
  digitalWrite(AIN1_PIN, HIGH);
  digitalWrite(AIN2_PIN, LOW);
  digitalWrite(BIN1_PIN, LOW);
  digitalWrite(BIN2_PIN, HIGH);

  analogWrite(PWMA_PIN, speed);
  analogWrite(PWMB_PIN, speed);
}

void Stop()
{
  Serial.println("Stopped");
  digitalWrite(AIN1_PIN, LOW);
  digitalWrite(AIN2_PIN, LOW);
  digitalWrite(BIN1_PIN, LOW);
  digitalWrite(BIN2_PIN, LOW);

  analogWrite(PWMA_PIN, 0);
  analogWrite(PWMB_PIN, 0); 
}



void IR_Pin_Setup()
{
  pinMode(leftIR, INPUT);
  pinMode(rightIR, INPUT);
}