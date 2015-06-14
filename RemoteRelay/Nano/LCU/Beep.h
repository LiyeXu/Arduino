#include "Arduino.h"
//-------------------------------------------------
//Access Beep
//-------------------------------------------------
#define beepPin 13
void setupBeep()
{
  pinMode(beepPin, OUTPUT);
}
void beep(int times)
{
  for(int i = 0; i < times; i++)
  {
    digitalWrite(beepPin, HIGH); delay(100);
    digitalWrite(beepPin, LOW); delay(50);  
  }
}
void beepOff()
{
  digitalWrite(beepPin, LOW);
}
////////////////////////////////////////////////////
