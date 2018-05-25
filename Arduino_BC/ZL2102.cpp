
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

void ZL2102::configure (void) {
  // Configure ON_OFF_CONFIG register
  // Device starts from OPERATION command only
  // Turn off the output immediately
  setByte8 (ZL2102_ON_OFF_CFG, 0b00011001);
  turnOff ();
  setVout(3.3);
  
}

void ZL2102::turnOn (void) {
  // On & margin state nominal
  setByte8 (ZL2102_OPERATION,  0b10000100);
}
void ZL2102::turnOff (void) {
  // Immediate off & margin state off
  setByte8 (ZL2102_OPERATION,  0b00000100);
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
float ZL2102::getFrequency (void) {
  uint16_t temp_L11 = smbus->readWord(pmbus_addr, ZL2102_FREQUENCY);
  return math_.lin11_to_float(temp_L11);;
}

void ZL2102::setVout (float vout) {
  if (vout > 0.55 && vout < 5.0) {
    pmbus->setVout (pmbus_addr, vout);
  }
}


void ZL2102::listAllParameter (void) {
  Serial.print("Vin : "); Serial.print(getVin());
  Serial.print(" Vout : "); Serial.print(getVout());  
  Serial.print(" Iout : "); Serial.print(getIout());
  Serial.print(" Pout : "); Serial.print(getPout());
  Serial.print(" Freq : "); Serial.print(getFrequency());
  Serial.print(" Temp : "); Serial.print(getTempearature());
  Serial.println();
}

