#include "Arduino.h"
//-------------------------------------------------
//Access DS3231 Timer
//-------------------------------------------------
DS3231 Clock;

bool timeUpdated = false; // ensure timer will only be updated for once on each calibration
void timerUpdate(int yy, int MM, int dd, int hh, int mm, int ss, int dw)
{
  if (timeUpdated) 
    return;
  Clock.setSecond(ss);//Set the second 
  Clock.setMinute(mm);//Set the minute 
  Clock.setHour(hh);  //Set the hour 
  Clock.setDoW(dw);    //Set the day of the week
  Clock.setDate(dd);  //Set the date of the month
  Clock.setMonth(MM);  //Set the month of the year
  Clock.setYear(yy);  //Set the year (Last two digits of the year)
  timeUpdated = true;
}

int second, minutes, hour, date, month, year, temperature, dow;
int lastMin = 0; // used to track every minutes
// return true if current minute != lastMin
bool timerRead()
{
  bool Century=false, h12=false, PM=false;
  second=Clock.getSecond();
  minutes=Clock.getMinute();
  bool ret = lastMin != minutes;
  lastMin = minutes;
  hour=Clock.getHour(h12, PM);
  date=Clock.getDate();
  month=Clock.getMonth(Century);
  year=Clock.getYear();  
  temperature=Clock.getTemperature();
  dow = Clock.getDoW();  
  return ret;
}
void timerPrint()
{
  _debugSerial.print(F("DateTime="));
  _debugSerial.print(F("20"));
  _debugSerial.print(year,DEC);
  _debugSerial.print(F("-"));
  _debugSerial.print(month,DEC);
  _debugSerial.print(F("-"));
  _debugSerial.print(date,DEC);
  _debugSerial.print(F(" "));
  _debugSerial.print(hour,DEC);
  _debugSerial.print(F(":"));
  _debugSerial.print(minutes,DEC);
  _debugSerial.print(F(":"));
  _debugSerial.print(second,DEC);
  _debugSerial.print(F("\n")); 
  _debugSerial.print(F("DayOfWeek="));
  switch(dow)
  {    
    case 0: _debugSerial.print(F("Sun.")); break;
    case 1: _debugSerial.print(F("Mon.")); break;
    case 2: _debugSerial.print(F("Tue.")); break;
    case 3: _debugSerial.print(F("Wed.")); break;
    case 4: _debugSerial.print(F("Thu.")); break;
    case 5: _debugSerial.print(F("Fri.")); break;
    case 6: _debugSerial.print(F("Sat.")); break;
    case 7: _debugSerial.print(F("Sun.")); break;
  }   
  _debugSerial.print(F("\n"));
  _debugSerial.print(F("Temperature="));
  _debugSerial.print(temperature); 
  _debugSerial.print(F("\n"));
}

void setupTimer(bool initTime = false)
{    
    delay(2000); // delay 2 sec before init I2C wire to avoid time lost 
    Wire.begin(); 
    if(initTime)
    {
      _debugSerial.println(F("Init Time!"));
      timerUpdate(15, 4, 21, 23, 40, 0, 2);
    }
}
///////////////////////////////////////////////////
