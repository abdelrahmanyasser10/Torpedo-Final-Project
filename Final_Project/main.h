#ifndef _MAIN_H
#define _MAIN_H

#include <WiFi.h>
#include <ESP32Servo.h>


/*------------------Communication Parameters Setup------------------*/
extern const char* ssid;
extern const char* password;

/*------------------Motors Pins------------------*/
// Left
#define enablePinA 14
#define motorPin1 27
#define motorPin2 26
// Right
#define enablePinB 5
#define motorPin3 18
#define motorPin4 19


/*------------------Servo Parameters Setup------------------*/
#define servoPin 13
extern int servoPos;



/*------------------Functions Decleration------------------*/
void communication_setup();
void motorDriver_setup();
void moveForward();
void moveBackward();
void turnRight();
void turnLeft();
void Stop();
void servo_setup();
void grip();
void keyboard_control();
void IR_setup();
void Line_Following_IR();
void ISR_Setup();
void ISR_countA();
void ISR_countB();

/*------------------IR Sensor Pins------------------*/
#define leftIR 32
#define rightIR 33

/*------------------encoder Pins------------------*/
extern const int encoder1;
extern const int encoder2;
extern const int stepcount;  // 20 Slots in disk, change if different
extern const int wheeldiameter; // Wheel diameter in millimeters, change if different
extern volatile int counter_A;
extern volatile int counter_B;
extern float wheelbase; // The distance between the two wheels of your robot in meters


// flag
extern bool flag;

#endif