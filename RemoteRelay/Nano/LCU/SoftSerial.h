#include "Arduino.h"
//-------------------------------------------------
//Soft Serial
//-------------------------------------------------
#define softSerial_RX A2
#define softSerial_TX A3
SoftwareSerial softSerial(softSerial_RX, softSerial_TX); 

void setupSoftSerial()
{
  softSerial.begin(9600);
}
