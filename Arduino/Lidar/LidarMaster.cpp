/*                LidarMaster.cpp
 * Autor:         ruti1014
 * Beschreibung:  I2C kommunikation mit dem Laserscanner
 * Hardware:      Benewake TF-Luna
 *                http://en.benewake.com/product/detail/5e1c1fd04d839408076b6255.html
 * 
*/

#include "Arduino.h"
#include "LidarMaster.h"
#include <Wire.h>



LidarMaster::LidarMaster(int ic2Adress){
  Wire.begin();
  _adress = ic2Adress;
}
uint16_t LidarMaster::getDistance(){
  return readIC216B(0x00);
}
uint16_t LidarMaster::getAmp(){
  return readIC216B(0x02);
}
uint16_t LidarMaster::getTemperatur(){
  return readIC216B(0x04)/100.0;
}


uint16_t LidarMaster::readIC216B(int reg) {
  uint16_t value = -1;
  selectRegister(reg);
  Wire.requestFrom(_adress, 2);
  while (Wire.available()) {
    value = Wire.read() | Wire.read() << 8;
  }
  return value;
}


void LidarMaster::selectRegister(int reg) {
  Wire.beginTransmission(_adress);
  Wire.write(reg);
  Wire.endTransmission();
}


void LidarMaster::writeData(int reg, byte value) {
  Wire.beginTransmission(_adress);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

int LidarMaster::getAdress(){
  return _adress;
}
