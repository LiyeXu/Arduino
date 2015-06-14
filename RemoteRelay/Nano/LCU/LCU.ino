// Pins:
// A
// A0:Potentiometer Acurate
// A1:Potentiometer
// A2:Soft RX
// A3:Soft TX
// A4:Timer I2C
// A5:Timer I2C
// A6:JoyStick X
// A7:JoyStick Y
// D2:IR Recv
// D3:IR Send
// D4:Relay
// D5:Light Sensor
// D6:Joy Stick Button / Toggle
// D7:Sound Sensor
// D8:Touch 1
// D9:Touch 2
// D10:Touch 3
// D11:Touch 4
// D12: IRHuman
// D13: Beep

#include "Relay.h"
#include <SoftwareSerial.h> 
#include "SoftSerial.h"
#define _debugSerial softSerial
#define _wifiSerial Serial
#include "Toggle.h"
#include <EEPROM.h>
#include "EEPROMAccessor.h"
#include <IRremote.h>
#include <IRremoteInt.h>
#include "IR.h"
#include <DS3231.h>
#include <Wire.h>
#include "Timer.h"
#include "EEPROMAccessor2.h"
#include "Potentiometer.h"
#include "Potentiometer2.h"
#include "TouchSwitch.h"
#include "Beep.h"
//#include "JoyStick.h"
#include "LightSensor.h"
#include "SoundSensor.h"
#include "HumanSensor.h"
#include "Buffer.h"
#include "Wifi.h"

void setup() {  
  setupRelay();
  Serial.begin(9600);
  setupSoftSerial();
  setupTimer(false);
  setupTouch();
  setupBeep(); 
  setupToggle();  
  setupIr(); 
  //setupJoyStick();
  setupLightSensor();
  setupSoundSensor();
  setupHumanSensor();
}
String wifiDid = "";
void save(int channel)
{
  unsigned int addr = channel*512;    
  unsigned int i = 0;
  int pageSize = 4;
  for(; i < irDecodeResults.rawlen / pageSize; i++)
    saveBytes2(addr + i * pageSize, (unsigned byte *)irDecodeResults.rawbuf + i * pageSize, pageSize);
  if(irDecodeResults.rawlen % pageSize != 0)
    saveBytes2(addr + i * pageSize, (unsigned byte *)irDecodeResults.rawbuf + i * pageSize, irDecodeResults.rawlen % pageSize);
  saveByte2(addr + i * pageSize + irDecodeResults.rawlen % pageSize, 255);
  _debugSerial.print(F("saved to channel: ")); _debugSerial.println(channel);  
}

void load(int channel)
{  
  unsigned int addr = channel*512;
  unsigned int i = 0;
  int pageSize = 30;
  for(; i < 512 / pageSize; i++)
  {
    loadBytes2(addr + i * pageSize, (unsigned byte *)(irDecodeResults.rawbuf) + i * pageSize, pageSize);
  }
  if(512 % pageSize != 0)
  {
    loadBytes2(addr + i * pageSize, (unsigned byte *)(irDecodeResults.rawbuf) + i * pageSize, 512 % pageSize);
  }
  for(int j = 0; j < 512; j++)
  {
    if((int)(irDecodeResults.rawbuf[j]) == 255)
    {
      irDecodeResults.rawlen = j;
      break;
    }
  }
  //irRecvPrint(&irDecodeResults);
  _debugSerial.print(F("loaded from channel: ")); _debugSerial.println(channel);  
}

void loop() {
  int level1 = potentiometerRead(0, 5000);
  int level2 = potentiometer2Read(0, 270);
  bool touch1 = touch1GetState();
  bool touch2 = touch2GetState();
  bool touch3 = touch3GetState();
  bool touch4 = touch4GetState();
  bool switchOn = toggleGetState();
  //bool jbutton = joyStickGetState();
  //int jx = joyStickReadX(-100, 100);
  //int jy = joyStickReadY(-100, 100);
  bool light = lightSensorGetState();
  bool sound = soundSensorGetState();
  bool human = humanSensorGetState();    
  /*_debugSerial.print("AccuratePotentiometer(A0)[0~5000]="); _debugSerial.println(level1); 
  _debugSerial.print("Potentiometer(A1)[0~270]="); _debugSerial.println(level2);
  _debugSerial.println("A2=SoftRx");
  _debugSerial.println("A3=SoftTx");
  _debugSerial.print("Touch1(D8)="); _debugSerial.println(touch1);
  _debugSerial.print("Touch2(D9)="); _debugSerial.println(touch2);
  _debugSerial.print("Touch3(D10)="); _debugSerial.println(touch3);
  _debugSerial.print("Touch4(D11)="); _debugSerial.println(touch4);
  _debugSerial.print("Button(D6)="); _debugSerial.println(switchOn);
  //_debugSerial.print("JoyStickButton(D6)="); _debugSerial.println(jbutton);
  //_debugSerial.print("JoyStickX(A6)="); _debugSerial.println(jx);
  //_debugSerial.print("JoyStickX(A7)="); _debugSerial.println(jy);
  _debugSerial.print("Light(D5)="); _debugSerial.println(light);
  _debugSerial.print("Sound(D7)="); _debugSerial.println(sound);
  _debugSerial.print("human(D12)="); _debugSerial.println(human);*/
  timerRead();
  //timerPrint();
  //if(switchOn || touch1 || touch2 || touch3 || touch4 || human)
  //  beep(1);
  if(wifiDid == "")
  {
    String& did = wifiRead(F("DID"));
    //_debugSerial.print("DID=");_debugSerial.println(did);    
    if(did == "")
    {
      delete &did;
    }
    else
    {
      wifiDid = did;
      wifiWrite(String(F("DIDACK=true\n")));
      _debugSerial.print(F("Wifi Connected! DID=")); _debugSerial.println(did);
      beep(2);
    }
  }
  else
  {
    // execute MQTT message command
    String& cmd = wifiRead(F("MQTT"));
    //_debugSerial.print("MQTT=");_debugSerial.println(cmd);
    if(cmd != "")
    {
      int idx = cmd.indexOf(F(":"));
      if(idx != -1)
      {
         String topic = cmd.substring(0, idx);
         String data = cmd.substring(idx + 1);
         if(topic == String(F("smartrelay")) + wifiDid)
         {           
           //_debugSerial.println(data);
           if (data == F("reset"))
           {
             asm volatile ("  jmp 0");  
           }
           else if(data == F("relay:on"))
           {
             relayOn();
           }
           else if(data == F("relay:off"))
           {
             relayOff();
           }    
           else if(data.startsWith(F("ir:recv")))
           {
             beep(1);
             int channel = data.substring(7).toInt();
             _debugSerial.print(F("decoding channel ")); _debugSerial.println(channel);
             irrecv.enableIRIn();
             bool ret = irRecvDecode();
             _debugSerial.println(ret);
             if(ret)
             {
               beep(2);
               save(channel);
             }     
           }
           else if(data.startsWith(F("ir:send")))
           {             
             int channel = data.substring(7).toInt();             
             _debugSerial.print(F("sending channel ")); _debugSerial.println(channel);
             load(channel);
             irSend(38);
           }
         }
      } 
    }
    delete &cmd;
    //_debugSerial.println("Upload Sensors Data...");
    // upload sensors data
    wifiWrite(F("sensors="));
    wifiWrite(F("\"{temperature:"));
    wifiWrite(String(temperature));
    wifiWrite(F(",light:"));
    wifiWrite(String(light));
    wifiWrite(F(",sound:"));
    wifiWrite(String(sound));
    wifiWrite(F(",human:"));
    wifiWrite(String(human));
    wifiWrite(F("}\"\n"));
    wifiWrite(F("dofile(\"connected.lua\")\n"));
  } 
}
