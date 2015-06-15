#include "Arduino.h"
//-------------------------------------------------
//Access Wifi Serial
//-------------------------------------------------
void wifiWrite(const String& command)
{
  //_debugSerial.println(command);
  _wifiSerial.print(command);
  _wifiSerial.flush();
}

String& wifiRead(const String& tagName)
{
  //_debugSerial.print("wait for "); _debugSerial.println(String(F("</")) + tagName + F(">"));
  waitResponse(String(F("</")) + tagName + F(">"), "", 5 * 1000);
  if(!isAtCmdTimeout && !isAtCmdFailed)
  {
    String& cmd = bufferExtract(String(F("<")) + tagName + F(">"), String(F("</")) + tagName + F(">"));
    return cmd;
  }  
  else if(isAtCmdTimeout)
  {
    //_debugSerial.println(F("Wifi Serial Timeout!"));
  }
  else if(isAtCmdFailed)
  {
    //_debugSerial.println(F("Wifi Polling Failed!"));
  }
  return *new String("");
}
////////////////////////////////////////////////////
