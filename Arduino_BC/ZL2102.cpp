
#include "ZL2102.h"

void ZL2102::init (LT_PMBus *pmbus_obj,LT_SMBus *smbus_obj, uint8_t _pmbus_addr, uint8_t _ID) {

  pmbus_addr = _pmbus_addr;
  pmbus = pmbus_obj;
  smbus = smbus_obj;
  ID = _ID;
}

ZL2102::ZL2102 (void) {

  pmbus_addr  = NULL;
  pmbus       = NULL;
  smbus       = NULL;
  isConfigured = false;

  data_name[DATA_POS_VIN] = "vin";
  data_name[DATA_POS_VOUT] = "vout";
  data_name[DATA_POS_IOUT] = "iout";
  data_name[DATA_POS_POUT] = "pout";
  data_name[DATA_POS_FREQ] = "freq";
  data_name[DATA_POS_TEMP] = "temp";
}
void ZL2102::configure (void) {
  // Configure ON_OFF_CONFIG register
  // Device starts from OPERATION command only
  // Turn off the output immediately
  setByte8 (ZL2102_ON_OFF_CFG, 0b00011001);

  // check error while configuring the dcdc
  
  setVout(5.0);
}

void ZL2102::smbus_transfer (void) {
  data_array[DATA_POS_VIN] = pmbus->readVin (pmbus_addr, false);
  data_array[DATA_POS_IOUT] = pmbus->readIout (pmbus_addr, false);
  data_array[DATA_POS_POUT] = pmbus->readPout (pmbus_addr, false);
  data_array[DATA_POS_FREQ] = math_.lin11_to_float(smbus->readWord(pmbus_addr, ZL2102_FREQUENCY));
  data_array[DATA_POS_TEMP] = math_.lin11_to_float(smbus->readWord(pmbus_addr, ZL2102_READ_TEMP));
}
void ZL2102::printAsJSON (void) {
  PRINT_JSTART
    Serial.print ("psu");Serial.print (":");Serial.print (ID);
    PRINT_JSTART
    for (uint8_t i=0; i!=DATA_ARRAY_SIZE;i++) {
      Serial.print (data_name[i]);
      Serial.print (":");
      Serial.print (data_array[i]);
      if (i != (DATA_ARRAY_SIZE-1))
        Serial.print (",");
    }
    PRINT_JSTOP
  PRINT_JSTOP
}

void ZL2102::turn (bool on_off) {
  if (on_off == true) {
    // On & margin state nominal
    setByte8 (ZL2102_OPERATION,  0b10000100);
  }
  else {
    // Immediate off & margin state off
    setByte8 (ZL2102_OPERATION,  0b00000100);
  }
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
  return math_.lin11_to_float(temp_L11);
}

bool ZL2102::setVout (float vout) {
  if (vout < 0.55) {
    //turnOff ();
    return true;
  }
  else if (vout > 0.55 && vout < 5.1) {
    pmbus->setVout (pmbus_addr, vout);
    return true;
  }

  return false;
}

void ZL2102::listAllParameter (void) {

  /*const size_t bufferSize = JSON_OBJECT_SIZE(7);
  DynamicJsonBuffer jsonBuffer(bufferSize);
  
  JsonObject& root = jsonBuffer.createObject();
  root["psu"] = ID;
  root["vin"] = getVin();
  root["vout"] = getVout();
  root["iout"] = getIout();
  root["freq"] = getFrequency ();
  root["pout"] = getPout ();
  root["temp"] = getTempearature();
  root.printTo(Serial);
  Serial.println("");
  */
}

