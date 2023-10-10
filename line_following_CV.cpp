#include "main.h"

void Line_Following_CV()
{
    if(CX >= 120)
        turnLeft(100);
    else if(CX < 120 && CX > 40)
        moveForward(150);
    else if(CX >= 40)
        turnRight(100);
}