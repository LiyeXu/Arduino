#include "Arduino.h"
//-------------------------------------------------
//Access Light Sensor
//-------------------------------------------------
#define lightSensorPin 5
void setupLightSensor()
{
  pinMode(lightSensorPin, INPUT);
}
bool lightSensorGetState()
{
  return digitalRead(lightSensorPin) == LOW;
}
////////////////////////////////////////////////////
