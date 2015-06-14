#include "Arduino.h"
//-------------------------------------------------
//Access Toggle Switch
//-------------------------------------------------
#define togglePin 6
void setupToggle()
{
  pinMode(togglePin, INPUT_PULLUP);
}
bool toggleGetState()
{
  return digitalRead(togglePin) == LOW;
}
////////////////////////////////////////////////////
