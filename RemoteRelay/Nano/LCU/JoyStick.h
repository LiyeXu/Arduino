#include "Arduino.h"
//-------------------------------------------------
//Access Joystick
//-------------------------------------------------
#define joyStickXPin  A6
#define joyStickYPin  A7
#define joyStickButtonPin 6
void setupJoyStick()
{
  pinMode(joyStickButtonPin, INPUT_PULLUP);
}
bool joyStickGetState()
{
  return digitalRead(joyStickButtonPin) == LOW;
}
int joyStickReadX(int minVal, int maxVal)
{
  int level = analogRead(joyStickXPin);
  return map(level, 0, 1023, minVal, maxVal);
}
int joyStickReadY(int minVal, int maxVal)
{
  int level = analogRead(joyStickYPin);
  return map(level, 0, 1023, minVal, maxVal);
}
////////////////////////////////////////////////////
