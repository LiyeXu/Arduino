#include "Arduino.h"
//-------------------------------------------------
//Relay
//-------------------------------------------------
#define relayPin 4
void relayOn()
{
  digitalWrite(relayPin, LOW);
}
void relayOff()
{  
  digitalWrite(relayPin, HIGH);
}
void setupRelay()
{
  pinMode(relayPin, OUTPUT);
  relayOff();
}
////////////////////////////////////////////////////
