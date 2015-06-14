#include "Arduino.h"
//-------------------------------------------------
//Access Human Sensor
//-------------------------------------------------
#define humanSensorPin 12
void setupHumanSensor()
{
  pinMode(humanSensorPin, INPUT);
}
bool humanSensorGetState()
{
  return digitalRead(humanSensorPin) == HIGH;
}
////////////////////////////////////////////////////
