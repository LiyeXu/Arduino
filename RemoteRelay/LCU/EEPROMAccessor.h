#include "Arduino.h"
//-------------------------------------------------
//Access EEPROM
//-------------------------------------------------
#define EEPROM_SIZE 1024
#define SSID_ADDR 0
#define PWD_ADDR 16

void saveString(int addr, const String& str)
{
  for(int i = 0 ; i < str.length(); i++)
  {
    if(addr >= EEPROM_SIZE)
    {
      _debugSerial.println(F("EEPROM overflow, data was trimed!"));
      return;
    }
    EEPROM.write(addr, str.charAt(i));
    addr++;    
  }  
  EEPROM.write(addr, '\0');
}

String& loadString(int addr)
{
  if(addr >= EEPROM_SIZE)
  {
    _debugSerial.println(F("EEPROM overflow, data was trimed!"));
    return *(new String(""));
  }
  String& ret = *(new String(""));
  char v = EEPROM.read(addr);
  while(v != '\0')
  {    
    ret += v;
    addr++;    
    if(addr >= EEPROM_SIZE)
    {
      _debugSerial.println(F("EEPROM overflow, data was trimed!"));
      return ret;
    }    
    v = EEPROM.read(addr);
  }
  return ret;
}
////////////////////////////////////////////////////
