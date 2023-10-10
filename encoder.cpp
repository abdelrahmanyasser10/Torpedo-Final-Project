#include "main.h"


void ISR_countA()  
{
  counter_A++;  // increment Motor A counter value
} 

// Motor B pulse count ISR
void ISR_countB()  
{
  counter_B++;  // increment Motor B counter value
}


float measure_distance(int Steps)
{
  // Calculate and print distance
  float circumference = ((wheeldiameter / 100) * PI) / 10;
  float cm_step = circumference / stepcount;
  float distance = Steps * cm_step;
  
  Serial.print("Distance covered: ");
  Serial.println(distance);
  
  return distance;
}

float measureStepsAndDistance()
{
  // Measure steps
  Serial.print("Steps by Motor1: ");
  Serial.println(counter_A);
  Serial.print("Steps by Motor2: ");
  Serial.println(counter_B);
  
  int Steps_A = counter_A;
  int Steps_B = counter_B;

  // Calculate and print distance
  float distance_A = measure_distance(Steps_A);
  float distance_B = measure_distance(Steps_B);
  
  Serial.print("Distance covered by Motor1: ");
  Serial.println(distance_A);
  
  Serial.print("Distance covered by Motor2: ");
  Serial.println(distance_B);

  float distance = (distance_A + distance_B) / 2;

  // Calculate rotation
  float rotation = (distance_A - distance_B) / wheelbase;
  
  Serial.print("Rotation (in radians): ");
  Serial.println(rotation);
  
  return distance; 
}



void encoder_setup()
{
  attachInterrupt(digitalPinToInterrupt (encoder1), ISR_countA, RISING);
  attachInterrupt(digitalPinToInterrupt (encoder2), ISR_countB, RISING);
}