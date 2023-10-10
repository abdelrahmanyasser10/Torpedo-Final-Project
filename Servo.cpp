#include "main.h"

void Servo_Control()
{
    if (flag == 0)
    {
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

        Serial.print("- Servo Position = ");
        Serial.println(servoPos);
    }
}

void attach_Servo_Pin()
{
   // attach servo pin
  servomotor.attach(SERVO_PIN);
  servomotor.write(servoPos);
}

void Servo_Control_Setup()
{
    Ps3.attach(Servo_Control);
}