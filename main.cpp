// main.cpp
#include "main.h"

// Define global variables
const int motorFreq = 1000;
const int motorResolution = 8;

const int motorAChannel = 3;
const int motorBChannel = 4;

int motorAPWM = 0;
int motorBPWM = 0;

bool motorDir = true;

int leftX = 0;
int leftY = 0;

int rightX = 0;
int rightY = 0;

Servo servomotor;

int servoPos = 90;

const int leftIR = 32;
const int rightIR = 33;

const uint8_t encoder1 = 18;
const uint8_t encoder2 = 19;

const float stepcount = 20.00;  
const float wheeldiameter = 66.10; 

volatile int counter_A = 0;
volatile int counter_B = 0;

float wheelbase = 0.14; 

bool flag1 = false; 
bool flag2 = false; 

WiFiServer server(8080); // Server on port 8080
const char* ssid = "ESP32-Access-Point";

int CX;

