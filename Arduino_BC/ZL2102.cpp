
#include "ZL2102.h"



void ZL2102::init (LT_PMBus *pmbus_obj,LT_SMBus *smbus_obj, uint8_t _pmbus_addr) {

  pmbus_addr = _pmbus_addr;
  pmbus = pmbus_obj;
  smbus = smbus_obj;

  
  pmbus->setVout (pmbus_addr, 1.0);
}

ZL2102::ZL2102 (void) {

  pmbus_addr  = NULL;
  pmbus       = NULL;
  smbus       = NULL;
}

float ZL2102::getVin(void) {
  float v = pmbus->readVin (pmbus_addr, false);
  return v;
}

