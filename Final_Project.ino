// Include PS3 Controller library
#include <Ps3Controller.h>
#include <ESP32Servo.h>
#include <driver/rmt.h>

// Define motor driver pins
#define PWMA_PIN 14
#define AIN1_PIN 27
#define AIN2_PIN 26
#define PWMB_PIN 5
#define BIN1_PIN 18
#define BIN2_PIN 19
// Servo Pin
#define SERVO_PIN 13


// Define PWM Parameters
const int motorFreq = 1000;
const int motorResolution = 8;

// Define channels for each motor
const int motorAChannel = 3;
const int motorBChannel = 4;

// Variables for Motor PWM values
int motorAPWM = 0;
int motorBPWM = 0;

// Variables for motor direction - true=forward
bool motorDir = true;

// Variables for joystick values
int rightX = 0;
int rightY = 0;
int leftX = 0;
int leftY = 0;

// Create servo object
Servo servomotor;

// Servo Position
int servoPos = 90;

// IR
const int leftIR = 32;
const int rightIR = 33;

// encoder
const uint8_t encoder1 = 18;
const uint8_t encoder2 = 19;
const float stepcount = 20.00;  // 20 Slots in disk, change if different
const float wheeldiameter = 66.10; // Wheel diameter in millimeters, change if different
volatile int counter_A = 0;
volatile int counter_B = 0;
float wheelbase = 0.14; // The distance between the two wheels of your robot in meters




// Flag for the control flow
bool flag = 1



// Callback Function
void notify() {

    if( Ps3.event.button_down.select)
    {
      Serial.println("flag before pressing select: ");
      Serial.println(flag);
      Serial.println("Started pressing the select button");
      flag = !flag;
      Serial.println("flag after pressing select: ");
      Serial.println(flag);
      
    }
    if (flag == 0)
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
    // Get Joystick value
      rightX = (Ps3.data.analog.stick.rx);
      rightY = (Ps3.data.analog.stick.ry);

      // Check if joystick was moved upward, indicating return to home (90 degrees)
      if (rightY < -100) {
        servoPos = 90;
        servomotor.write(servoPos);
        delay(10);
      } else {

        // See if joystick was moved left or right, and in what direction. If moved, move servo in that direction
        if (rightX < -10 && servoPos < 180) {
          servoPos += 5;
          servomotor.write(servoPos);
          delay(10);
        }
        if (rightX > 10 && servoPos > 0) {
          servoPos -= 5;
          servomotor.write(servoPos);
          delay(10);
        }
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
      Serial.print("- Servo Position = ");
      Serial.println(servoPos);
    }

}

// On Connection function
void onConnect() {
  // Print to Serial Monitor
  Serial.println("Connected.");
}

void onDisconnect()
{
  Stop();
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





void Line_Following()
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

void measureStepsAndDistance()
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

    // Calculate rotation
    float rotation = (distance_A - distance_B) / wheelbase;
    
    Serial.print("Rotation (in radians): ");
    Serial.println(rotation);
}



void setup() {

  // Setup Serial Monitor for testing
  Serial.begin(115200);

  // Define On Connection Function
  Ps3.attachOnConnect(onConnect);
  Ps3.attachOnDisconnect(onDisconnect);

  // Define Callback Function
  Ps3.attach(notify);

  // Emulate console as specific MAC address (change as required)
  Ps3.begin("38:4f:f0:c3:c4:9e");


  // Set motor controller pins as outputs
  pinMode(PWMA_PIN, OUTPUT);
  pinMode(PWMB_PIN, OUTPUT);
  pinMode(AIN1_PIN, OUTPUT);
  pinMode(AIN2_PIN, OUTPUT);
  pinMode(BIN1_PIN, OUTPUT);
  pinMode(BIN2_PIN, OUTPUT);

  // attach servo pin
  servomotor.attach(SERVO_PIN);
  servomotor.write(servoPos);

  // Set channel Parameters for each motor
  ledcSetup(motorAChannel, motorFreq, motorResolution);
  ledcSetup(motorBChannel, motorFreq, motorResolution);

  // Attach Motor PWM pins to corresponding channels
  ledcAttachPin(PWMA_PIN, motorAChannel);
  ledcAttachPin(PWMB_PIN, motorBChannel);

  // Print to Serial Monitor
  Serial.println("Ready.");

  attachInterrupt(digitalPinToInterrupt (encoder1), ISR_countA, RISING);
  attachInterrupt(digitalPinToInterrupt (encoder2), ISR_countB, RISING);

  pinMode(leftIR, INPUT);
  pinMode(rightIR, INPUT);


}

void loop() {
  
  if (!Ps3.isConnected())
  {
    Serial.println("Not Connected");
  }

  if(flag == 1)
  {
    Line_Following();
  }

  delay(2000);

}
