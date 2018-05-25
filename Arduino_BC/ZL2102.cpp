
#include "ZL2102.h"



void ZL2102::init (LT_PMBus *pmbus_obj,LT_SMBus *smbus_obj, uint8_t _pmbus_addr) {

  pmbus_addr = _pmbus_addr;
  pmbus = pmbus_obj;
  smbus = smbus_obj;
  //
}

ZL2102::ZL2102 (void) {

  pmbus_addr  = NULL;
  pmbus       = NULL;
  smbus       = NULL;
}

void ZL2102::turnOn (void) {
  Serial.println("Turn On");
  delay(10);
  setByte8 (ZL2102_ON_OFF_CFG, ZL2102_TURN_ON_CFG_ON);
  
  Serial.println(getByte8(ZL2102_ON_OFF_CFG), BIN);
}
void ZL2102::turnOff (void) {
  Serial.println("Turn Off");
  delay(10);
  
  setByte8 (ZL2102_ON_OFF_CFG, ZL2102_TURN_ON_CFG_OFF);
 // Serial.println(getByte8(ZL2102_ON_OFF_CFG), BIN);
}

uint16_t ZL2102::getWord16 (uint8_t cmd) {
  uint16_t data_word = smbus->readWord(pmbus_addr, cmd);
  return data_word;
}
void ZL2102::setWord16 (uint8_t cmd, uint16_t bitmask) {
  smbus->writeWord (pmbus_addr, cmd, bitmask);
}

uint8_t ZL2102::getByte8 (uint8_t cmd) {
  uint8_t data_word = smbus->readByte(pmbus_addr, cmd);
  return data_word;
}
void ZL2102::setByte8 (uint8_t cmd, uint8_t bitmask) {
  smbus->writeByte (pmbus_addr, cmd, bitmask);
}

float ZL2102::getIout (void) {
  float i = pmbus->readIout (pmbus_addr, false);
  return i;
}
float ZL2102::getPout (void) {
  float p = pmbus->readPout (pmbus_addr, false);
  return p;
}
float ZL2102::getTempearature (void) {
  uint16_t temp_L11 = smbus->readWord(pmbus_addr, ZL2102_READ_TEMP);
  return math_.lin11_to_float(temp_L11);
}

float ZL2102::getVout (void) {
  float v = pmbus->readVout (pmbus_addr, false);
  return v;
}
float ZL2102::getVin(void) {
  float v = pmbus->readVin (pmbus_addr, false);
  return v;
}
void ZL2102::setVout (float vout) {
  if (vout > 0.55 && vout < 5.0) {
    pmbus->setVout (pmbus_addr, vout);
  }
}

void    lisAllParameter (void) {

    
}

