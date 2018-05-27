
#include "BoardCaptain.h"

#define ZL2102_ADDR_1   0x20
#define ZL2102_ADDR_2   0x21
#define ZL2102_ADDR_3   0x22

// Initialize IOs and Communication ports
BoardCaptain::BoardCaptain (void) {

  pinMode (OUT_nLED_RG, OUTPUT);
  state_led (BC_ERROR);

  pinMode(OUT_SET_VADJ_VS0, OUTPUT);
  pinMode(OUT_SET_VADJ_VS1, OUTPUT);
  pinMode(OUT_SET_VADJ_VS2, OUTPUT);
  pinMode(OUT_EN_VADJ_1,    OUTPUT);

  pinMode(ADC_12V_INPUT, INPUT);
 
  enable_vadj (false);                // disable adjustable voltage controller

  smbus = new LT_SMBusNoPec();
  pmbus = new LT_PMBus(smbus);

  dcdc1.init (pmbus, smbus, ZL2102_ADDR_1);
  dcdc2.init (pmbus, smbus, ZL2102_ADDR_2);
  dcdc3.init (pmbus, smbus, ZL2102_ADDR_3);
  
  dcdc1.configure ();
  dcdc2.configure ();
  dcdc3.configure ();

  initTemperatureSensors( );

  pinMode (SYSTEM_EN, INPUT);
  sense_enable_input ( );      // update

  state_led (BC_OK);
  dcdc2.turnOn();
  dcdc3.turnOn();

  initFans ();

}
void BoardCaptain::initTemperatureSensors (void) {

  ntc1 = new NTC ();
  ntc2 = new NTC ();
  ntc_int = new NTC ();
  
  ntc1->init_103AT2(ADC_TEMP_1, REF_RES, 10);
  ntc2->init_NCP15XW(ADC_TEMP_2, REF_RES, 10);
  ntc2->init_NCP15XW(ADC_TEMP_INTERN, 10500, 10);   // diffrent voltage 
}
void BoardCaptain::run_system (void) {
 
  ntc1->measureTemperature();
  ntc2->measureTemperature();

  senseFans ();

  //Serial.println(sense_input_voltage());
  if (sense_enable_input()) {
    state_led (BC_OK);
    //dcdc2.turnOn();
  }
  else {
    state_led (BC_ERROR);
    dcdc2.turnOff();
  }

  //dcdc1.listAllParameter();
 
}
bool BoardCaptain::setVout (uint8_t psu, float voltage) {
  bool error = false;
  switch (psu) {
      case 0 : error = dcdc1.setVout (voltage); break;
      case 1 : error = dcdc2.setVout (voltage); break;
      case 2 : error = dcdc3.setVout (voltage); break;
    }
    Serial.print ("PSU : ");Serial.print (psu);
    Serial.print (" Voltage : ");Serial.println (voltage);
  return error;
}
float BoardCaptain::getVout (uint8_t psu){
  float retval = 0;
  switch (psu) {
      case 0 : retval = dcdc1.getVout ( ); break;
      case 1 : retval = dcdc2.getVout ( ); break;
      case 2 : retval = dcdc3.getVout ( ); break;
      default : retval = -1; break;
    }
    return retval;
}
float BoardCaptain::getVin (uint8_t psu) {
  float retval = 0;
  switch (psu) {
      case 0 : retval = dcdc1.getVin ( ); break;
      case 1 : retval = dcdc2.getVin ( ); break;
      case 2 : retval = dcdc3.getVin ( ); break;
      default : retval = -1; break;
    }
    return retval;
}
float BoardCaptain::getIout (uint8_t psu) {
  float retval = 0;
  switch (psu) {
      case 0 : retval = dcdc1.getIout ( ); break;
      case 1 : retval = dcdc2.getIout ( ); break;
      case 2 : retval = dcdc3.getIout ( ); break;
      default : retval = -1; break;
    }
    return retval;
}
float BoardCaptain::getPout (uint8_t psu) {
  float retval = 0;
  switch (psu) {
      case 0 : retval = dcdc1.getPout ( ); break;
      case 1 : retval = dcdc2.getPout ( ); break;
      case 2 : retval = dcdc3.getPout ( ); break;
      default : retval = -1; break;
    }
    return retval;
}

// +++++++++++++++++++++++++++++++ +++++++++++++++++++++++++++++++ +++++++++++++++++++++++++++++++
void BoardCaptain::initFans (void) {
  fan1 = new FanController(FAN_TACH_1, SENSOR_THRESHOLD, FAN_DRIVE_1);
  fan2 = new FanController(FAN_TACH_2, SENSOR_THRESHOLD, FAN_DRIVE_2);
  fan1->begin();
  fan2->begin();
}
void BoardCaptain::senseFans (void) {
  unsigned int rpms1 = fan1->getSpeed(); // Send the command to get RPM
  unsigned int rpms2 = fan2->getSpeed(); // Send the command to get RPM

  uint8_t target = 50;
  fan1->setDutyCycle(target);
  fan2->setDutyCycle(target);
}
// +++++++++++++++++++++++++++++++ +++++++++++++++++++++++++++++++ +++++++++++++++++++++++++++++++

bool BoardCaptain::sense_enable_input (void) {
  if (digitalRead (SYSTEM_EN) == HIGH) {
    system_enabled = false;
  }
  else {
    system_enabled = true;
  }
  return system_enabled;
}
void BoardCaptain::search_smbus_devices (void) {
  uint8_t *addr;
  addr = smbus->probe(0);
  while (*addr != 0) {
    Serial.print(F("ADDR 0x"));
    Serial.println(*addr++, HEX);
  }
}
void BoardCaptain::error_handler (const char *err_msg) {
  Serial.print ("Error: ");
  Serial.println(err_msg);
}
void BoardCaptain::vadj_set_outputs (uint8_t VS2, uint8_t VS1, uint8_t VS0) {
  digitalWrite (OUT_SET_VADJ_VS0, VS0);
  digitalWrite (OUT_SET_VADJ_VS0, VS1);
  digitalWrite (OUT_SET_VADJ_VS2, VS2);
}
void BoardCaptain::enable_vadj (bool enable) {
  if (enable) digitalWrite (OUT_EN_VADJ_1, HIGH);
  else        digitalWrite (OUT_EN_VADJ_1, LOW);
}
void BoardCaptain::set_vadj (VADJ voltage) {
  switch (voltage) {
    case (V_3V3): vadj_set_outputs(LOW, LOW, LOW);
      break;
    case (V_2V5): vadj_set_outputs(LOW, LOW, HIGH);
      break;
    case (V_1V8): vadj_set_outputs(LOW, HIGH, LOW);
      break;
    case (V_1V5): vadj_set_outputs(LOW, HIGH, HIGH);
      break;
    case (V_1V25): vadj_set_outputs(HIGH, LOW, LOW);
      break;
    case (V_1V2): vadj_set_outputs(HIGH, LOW, HIGH);
      break;
    case (V_0V8): vadj_set_outputs(HIGH, HIGH, LOW);
      Serial.println("set Vadj to 0.8V");
      break;
    default: error_handler("Vadj error, not implemented");
      break;
  }
}
void  BoardCaptain::state_led (LED_STATE state) {
  if (state == BC_ERROR)    digitalWrite (OUT_nLED_RG, LOW);
  else if (state == BC_OK)  digitalWrite (OUT_nLED_RG, HIGH);
}
float BoardCaptain::sense_input_voltage (void) {
  // Voltage divider 100k to 20k to 12V = factor 6
  return ((analogRead(ADC_12V_INPUT)/1023.) * ADC_REF_VOLTAGE * 6) ;
}
double BoardCaptain::getTempIntern (void) {
  // Depends on DCDC1 to be 5.0V
  return ntc_int->getTemperature();
}
float BoardCaptain::getTempFan1 (void) {
  return ntc1->getTemperature();
}
float BoardCaptain::getTempFan2 (void) {
  return ntc1->getTemperature();
}



