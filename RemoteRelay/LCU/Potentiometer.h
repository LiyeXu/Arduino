#include "Arduino.h"
//-------------------------------------------------
//Access Potentiometer
//-------------------------------------------------
#define potentiometerPin A0
int potentiometerRead(int minVal, int maxVal)
{
  int level = analogRead(potentiometerPin);
  return map(level, 0, 1023, minVal, maxVal);
}
////////////////////////////////////////////////////
