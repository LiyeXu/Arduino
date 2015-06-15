#include "Arduino.h"
//-------------------------------------------------
//Access IR
//-------------------------------------------------

#define irrecvPin 2
IRrecv irrecv(irrecvPin);
decode_results irDecodeResults;
IRsend irsend;
void setupIr()
{
  irrecv.enableIRIn(); 
  irsend.attachResult(&irDecodeResults);
}
void irRecvPrint(decode_results *results) {
  _debugSerial.println(F("IR Decoded"));  
  int count = results->rawlen;
  _debugSerial.print(F("Raw ("));
  _debugSerial.print(count, DEC);
  _debugSerial.print(F("):")); 
  for (int i = 0; i < count; i++) {
    _debugSerial.print((unsigned int)(results->rawbuf[i]), DEC);
    _debugSerial.print(F(" "));
  }
  _debugSerial.println();
}

bool irRecvDecode()
{        
  long start = millis();
  while(millis() - start < 15000)
  {
    if(irrecv.decode(&irDecodeResults))
    {        
       //irRecvPrint(&irDecodeResults);      
       return true;
    }
  }
  return false;
}
void irSend(int hz, bool sendgap = false)
{ 
  irsend.sendRawDirectly(&irDecodeResults, hz, sendgap);
}
///////////////////////////////////////////////////
