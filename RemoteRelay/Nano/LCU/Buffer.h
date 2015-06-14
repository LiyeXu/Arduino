#include "Arduino.h"
//-------------------------------------------------
//General Purpose Buffer
//-------------------------------------------------
#define BUFFER_SIZE 512
uint16_t bufferCursor;

#if defined(IRremoteint_h)
char* buffer = (char*)irparams.rawbuf;
#else
char buffer [BUFFER_SIZE];
#endif

String responseTrueKeywords[2];

void setResponseTrueKeywords(const String& w1, const String& w2) {
  responseTrueKeywords[0] = w1;
  responseTrueKeywords[1] = w2;
}

// find given keywords in buffer
boolean bufferFindAny(const String * keywords, int length = 2) {
  for (int i = 0; i < length; i++) {
    if (keywords[i] != NULL && keywords[i].length() > 0) {
      if (strstr(buffer, keywords[i].c_str()) != NULL) {
        return true;
      }
    }
  }
  return false;
}

boolean bufferFind(const String& keyword) {
  return bufferFindAny(&keyword, 1);
}

// Copy the buffer substring to dest, which starts from pStart + startLen and ends at pEnd
String& bufferExtract(const String& strStart, const String& strEnd)
{
  char * pStart = strstr(buffer, strStart.c_str());
  if(pStart == NULL)
  {
    _debugSerial.println(F("Start signature not found!"));
    return *(new String(""));
  }
  char * pEnd = strstr(pStart + strStart.length(), strEnd.c_str());
  if(pEnd == NULL)
  {
    _debugSerial.println(F("End signature not found!"));
    return *(new String(""));
  }
  int retLen = pEnd - pStart - strStart.length();
  //_debugSerial.print(F("retLen = "));_debugSerial.println(retLen);    
  String& ret = *(new String(""));
  for(int i = 0; i < retLen; i++)
  {
    ret += *(pStart + strStart.length() + i);
  }
  return ret;
}


bool isAtCmdTimeout = false;
bool isAtCmdFailed = false;

void waitResponse(const String& keyword, const String& keyword2 = "", unsigned long timeout = 5000)
{
  unsigned long start;
  start = millis();
  bufferCursor = 0;
  setResponseTrueKeywords(keyword, keyword2);
  isAtCmdTimeout = true;
  while (millis() - start < timeout) {
    if (_wifiSerial.available() > 0)
    {
      buffer[bufferCursor] = _wifiSerial.read();
      _debugSerial.write(buffer[bufferCursor]);
      bufferCursor++;      
    }
    buffer[bufferCursor] = '\0';
    if (bufferFindAny(responseTrueKeywords))
    {
      isAtCmdTimeout = false;
      isAtCmdFailed = false;      
      break;
    }
    else if (bufferFind(F("Fail")))
    {
      isAtCmdFailed = true;
      isAtCmdTimeout = false;
      break;
    }
  }
  //if (isAtCmdTimeout)
  {
    //_debugSerial.print(F("Wait response timeout in "));Serial.print(timeout);Serial.println(F("ms!"));
  }
  //else if (isAtCmdFailed)
  {
    //_debugSerial.println(F("Failed!"));
  }
  //_debugSerial.println(buffer);
}
