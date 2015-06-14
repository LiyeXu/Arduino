#include "Arduino.h"
//-------------------------------------------------
//Access Touch Switch
//-------------------------------------------------

#define touchPin1 8
#define touchPin2 9
#define touchPin3 10
#define touchPin4 11
void setupTouch()
{
  pinMode(touchPin1, INPUT); 
  pinMode(touchPin2, INPUT); 
  pinMode(touchPin3, INPUT); 
  pinMode(touchPin4, INPUT);   
}
bool touch1GetState()
{
  return digitalRead(touchPin1) == HIGH;
}
bool touch2GetState()
{
  return digitalRead(touchPin2) == HIGH;
}
bool touch3GetState()
{
  return digitalRead(touchPin3) == HIGH;
}
bool touch4GetState()
{
  return digitalRead(touchPin4) == HIGH;
}
///////////////////////////////////////////////////
