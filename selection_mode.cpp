#include "main.h"

void selection_mode()
{
    if( Ps3.event.button_down.select)
    {
      Serial.println("flag1 before pressing select: ");
      Serial.println(flag1);
      Serial.println("Started pressing the select button");
      flag1 = !flag1;
      Serial.println("flag1 after pressing select: ");
      Serial.println(flag1);
    }
    else if(Ps3.event.button_down.start)
    {
      Serial.println("flag2 before pressing select: ");
      Serial.println(flag2);
      Serial.println("Started pressing the select button");
      flag2 = !flag2;
      Serial.println("flag2 after pressing select: ");
      Serial.println(flag2);
    }
}

void selection_mode_setup()
{
    Ps3.attach(selection_mode);
}