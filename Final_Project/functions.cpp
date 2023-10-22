#include "main.h"
WiFiServer server(8080); //port 8080
Servo myServo;

/*------------------Communication Setup------------------*/
void communication_setup()
{
  // set up the Wifi mode to Access Point
  WiFi.mode(WIFI_AP);

  Serial.println("Configuring Access Point ....");
  //Creat the access point
  WiFi.softAP(ssid,password);

  // gets the IP of the created AP
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  
  server.begin();
}


/*------------------Motors Pin Setup------------------*/
void motorDriver_setup()
{
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enablePinA, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode(enablePinB, OUTPUT);
}

/*------------------Moving Forward------------------*/
void moveForward()
{
  Serial.println("Moving Forward");
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW); 
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  analogWrite(enablePinA, 170); 
  analogWrite(enablePinB, 180); 
}

/*------------------Moving Backward------------------*/
void moveBackward()
{
  Serial.println("Moving backward");
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH); 
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH); 
  analogWrite(enablePinA, 170);
  analogWrite(enablePinB, 180);
}

/*------------------Turning Right------------------*/
void turnRight()
{
  Serial.println("Turning right");
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);

  analogWrite(enablePinA, 0);
  analogWrite(enablePinB, 100);
}

/*------------------Turning left------------------*/
void turnLeft()
{
  Serial.println("Turning left");
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);

  analogWrite(enablePinA, 90);
  analogWrite(enablePinB, 0);
}

/*------------------STOP------------------*/
void Stop()
{
  Serial.println("STOP");
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);

  analogWrite(enablePinA, 0);
  analogWrite(enablePinB, 0); 
}


/*------------------Servo Pin Setup------------------*/
void servo_setup()
{
  myServo.attach(servoPin);
}

/*------------------Giving Angles to the Servo------------------*/
void grip(int servoPos)
{
  Serial.print("Gripper Angle: ");
  Serial.println(servoPos);
  myServo.write(servoPos);
}

/*------------------Handling data from the keyboard------------------*/
void keyboard_control()
{
  // Check if a client has connected
  WiFiClient client = server.available();

  if (client) {
    // Read the data from the client
    while (client.connected()) {
      while (client.available()) {
        char request = client.read();  // read a byte
        Serial.println(request);
        // Check the request and do actions accordingly
        // Move Forward
        if(request == 'f')
          moveForward();
        //Move Backward
        else if(request == 'b')
          moveBackward();
        // Turn Right
        else if(request == 'r')
          turnRight();
        // Turn Left
        else if(request == 'l')
          turnLeft();
        // STOP
        else if (request == 's')
          Stop();
        // Set the gripper to angle 0
        else if(request == '0')
          grip(50);
        // Set the gripper to angle 45
        else if(request == '1')
          grip(60);
        // Set the gripper to angle 90
        else if(request == '2')
          grip(70);
        // Set the gripper to angle 135
        else if(request == '3')
          grip(80);
        // Set the gripper to angle 180
        else if(request == '4')
          grip(90);
        else if(request == '5')
          grip(100);
        else if(request == '6')
          grip(110);
        else if(request == '7')
          grip(120);
        else if(request == '8')
          grip(130);
        else if(request == '9')
          grip(140);
        else if(request == 'i')
          flag = false;
      }
    }
    // if the communication is disconnected, try to reconnect it 
    if (WiFi.status() != WL_CONNECTED) {
      // If not, try to reconnect
      WiFi.reconnect();
    }
  }
}




void IR_setup()
{
  pinMode(leftIR, OUTPUT);
  pinMode(rightIR, OUTPUT);
}


void Line_Following_IR()
{
    Serial.println(digitalRead(leftIR));
    Serial.println(digitalRead(rightIR));

    if(digitalRead(leftIR)==0 && digitalRead(rightIR)==0)
      moveForward();
    else if(digitalRead(leftIR)==0 && !digitalRead(rightIR)==0)
      turnLeft();
    else if(!digitalRead(leftIR)==0 && digitalRead(rightIR)==0)
      turnRight();
    else if(!digitalRead(leftIR)==0 && !digitalRead(rightIR)==0)
    {
      Stop();
    }
  
}



/*------------------Encoder/Interrupt Pins Setup------------------*/
void ISR_Setup()
{
  attachInterrupt(digitalPinToInterrupt (encoder1), ISR_countA, RISING);
  attachInterrupt(digitalPinToInterrupt (encoder2), ISR_countB, RISING);
}


void ISR_countA()  
{
  counter_A++;  // increment Motor A counter value
  Serial.print("Encoder1: ");
  Serial.print(counter_A);
} 

// Motor B pulse count ISR
void ISR_countB()  
{
  counter_B++;  // increment Motor B counter value
  Serial.print(" - Encoder2: ");
  Serial.println(counter_B);
}


float measure_distance(int Steps)
{
    // Calculate and print distance
    float circumference = (wheeldiameter * PI) / 10;
    float cm_step = circumference / stepcount;
    float distance = Steps * cm_step;
    
    Serial1.print("Distance covered: ");
    Serial1.println(distance);
    
    return distance;
}

void measureStepsAndDistance()
{
    // Measure steps
    Serial1.print("Steps by Motor1: ");
    Serial1.println(counter_A);
    Serial1.print("Steps by Motor2: ");
    Serial1.println(counter_B);
    
    int Steps_A = counter_A;
    int Steps_B = counter_B;

    // Calculate and print distance
    float distance_A = measure_distance(Steps_A);
    float distance_B = measure_distance(Steps_B);
    
    Serial1.print("Distance covered by Motor1: ");
    Serial1.println(distance_A);
    
    Serial1.print("Distance covered by Motor2: ");
    Serial1.println(distance_B);

    // Calculate rotation
    float rotation = (distance_A - distance_B) / wheelbase;
    
    Serial1.print("Rotation (in radians): ");
    Serial1.println(rotation);
}

