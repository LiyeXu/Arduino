#include "Arduino.h"
//-------------------------------------------------
//Access Sound Sensor
//-------------------------------------------------
#define soundSensorPin 7
void setupSoundSensor()
{
  pinMode(soundSensorPin, INPUT);
}
bool soundSensorGetState()
{
  return digitalRead(soundSensorPin) == LOW;
}
////////////////////////////////////////////////////
