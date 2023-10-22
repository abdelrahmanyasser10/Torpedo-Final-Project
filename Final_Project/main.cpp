#include "main.h"

/*----------------------Variables-------------------*/
int servoPos = 0;

const char* ssid = "ESP32-Access-Point";
const char* password = "123456789";
const int encoder1 = 35;
const int encoder2 = 34;
const int stepcount = 20.00;  // 20 Slots in disk, change if different
const int wheeldiameter = 66.10; // Wheel diameter in millimeters, change if different
volatile int counter_A = 0;
volatile int counter_B = 0;
float wheelbase = 0.14; // The distance between the two wheels of your robot in meters
bool flag = true;
