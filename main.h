#ifndef _MAIN_H
#define _MAIN_H

#include <Ps3Controller.h>
#include <ESP32Servo.h>
#include <driver/rmt.h>
#include <WiFi.h>
#include <Wire.h>


// Define motor driver pins
#define PWMA_PIN 14
#define AIN1_PIN 27
#define AIN2_PIN 26
#define PWMB_PIN 5
#define BIN1_PIN 18
#define BIN2_PIN 19
// Servo Pin
#define SERVO_PIN 13

// Declare global variables
extern const int motorFreq;
extern const int motorResolution;
extern const int motorAChannel;
extern const int motorBChannel;
extern int motorAPWM;
extern int motorBPWM;
extern bool motorDir;
extern int leftX;
extern int leftY;
extern int rightX;
extern int rightY;
extern Servo servomotor;
extern int servoPos;
extern const int leftIR;
extern const int rightIR;
extern const uint8_t encoder1;
extern const uint8_t encoder2;
extern const float stepcount;
extern const float wheeldiameter;
extern volatile int counter_A;
extern volatile int counter_B;
extern float wheelbase;
extern bool flag1;
extern bool flag2;
extern WiFiServer server(8080); // Server on port 8080
extern const char* ssid;
extern int CX;
extern int CY;



// Declare functions

// Setup Functions
void PS3_Controller_Setup();
void communication_setup();
void selection_mode_setup();
void dcMotors_Pins_Setup();
void dcMotors_Control_Setup();
void attach_Servo_Pin();
void Servo_Control_Setup();
void IR_Pin_Setup();
void encoder_setup();


// Functions
void selection_mode_setup();
void moveMotors(int mtrAspeed, int mtrBspeed, bool mtrdir);
void Servo_Control();
void Line_Following_IR();
void moveForward(int speed);
void moveBackward(int speed);
void turnRight(int speed);
void turnLeft(int speed);
void Stop();
void ISR_countA();
void ISR_countB();
float measure_distance(int Steps);
float measureStepsAndDistance();
void receive();
void Line_Following_CV();


#endif
