#include "Arduino.h"
//-------------------------------------------------
//Access DS3231 I2C EEPROM
//-------------------------------------------------
void saveByte2(unsigned int addr, byte data, int deviceaddress = 0x57) {
  int rdata = data;
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(addr >> 8)); // MSB
  Wire.write((int)(addr & 0xFF)); // LSB
  Wire.write(rdata);
  Wire.endTransmission();
  delay(5);
}

// WARNING: address is a page address, 6-bit end will wrap around
// also, data can be maximum of about 30 bytes, because the Wire library has a buffer of 32 bytes
void saveBytes2(unsigned int addrpage, byte* data, byte length, int deviceaddress = 0x57) {
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(addrpage >> 8)); // MSB
  Wire.write((int)(addrpage & 0xFF)); // LSB
  byte c;
  for ( c = 0; c < length; c++)
    Wire.write(data[c]);
  Wire.endTransmission();
  delay(5);
}
             
byte loadByte2(unsigned int addr, int deviceaddress = 0x57) {
  byte rdata = 0xFF;
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(addr >> 8)); // MSB
  Wire.write((int)(addr & 0xFF)); // LSB
  Wire.endTransmission();
  Wire.requestFrom(deviceaddress,1);
  if (Wire.available()) rdata = Wire.read();
  return rdata;
}

// maybe let's not read more than 30 or 32 bytes at a time!
void loadBytes2(unsigned int addr, byte *buffer, int length, int deviceaddress = 0x57) {
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(addr >> 8)); // MSB
  Wire.write((int)(addr & 0xFF)); // LSB
  Wire.endTransmission();
  Wire.requestFrom(deviceaddress,length);
  int c = 0;
  for ( c = 0; c < length; c++ )
    if (Wire.available()) buffer[c] = Wire.read();
}
