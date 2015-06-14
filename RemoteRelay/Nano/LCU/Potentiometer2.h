#include "Arduino.h"
//-------------------------------------------------
//Access Potentiometer 2
//-------------------------------------------------
#define potentiometerPin2 A1
int potentiometer2Read(int minVal, int maxVal)
{
  int level = analogRead(potentiometerPin2);
  return map(level, 0, 1023, minVal, maxVal);
}
////////////////////////////////////////////////////
