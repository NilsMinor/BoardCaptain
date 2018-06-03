
#include "BoardCaptain.h"

#define ZL2102_ADDR_1   0x20
#define ZL2102_ADDR_2   0x21
#define ZL2102_ADDR_3   0x22

unsigned long previousMillis = 0;

// Initialize IOs and Communication ports
BoardCaptain::BoardCaptain (void) {

  pinMode (OUT_nLED_RG, OUTPUT);
  state_led (BC_ERROR);

  pinMode(OUT_SET_VADJ_VS0, OUTPUT);
  pinMode(OUT_SET_VADJ_VS1, OUTPUT);
  pinMode(OUT_SET_VADJ_VS2, OUTPUT);
  pinMode(OUT_EN_VADJ_1,    OUTPUT);

  pinMode(ADC_12V_INPUT, INPUT);
 
  smbus = new LT_SMBusNoPec();
  pmbus = new LT_PMBus(smbus);

  dcdc1.init (pmbus, smbus, ZL2102_ADDR_1, 0);
  dcdc2.init (pmbus, smbus, ZL2102_ADDR_2, 1);
  dcdc3.init (pmbus, smbus, ZL2102_ADDR_3, 2);
  
  dcdc1.configure ();
  dcdc2.configure ();
  dcdc3.configure ();

  initTemperatureSensors( );

  pinMode (SYSTEM_EN, INPUT);
  sense_enable_input ( );      // update

  state_led (BC_OK);
  dcdc1.turn(false);
  dcdc2.turn(false);
  dcdc3.turn(false);

  initFans ();

  data_name[DATA_POS_VIN] = "vin";
  data_name[DATA_POS_EN] = "en";
  data_name[DATA_POS_TINT] = "tint";
  data_name[DATA_POS_T1] = "temp1";
  data_name[DATA_POS_T2] = "temp2";
  data_name[DATA_POS_FAN1] = "fan1";
  data_name[DATA_POS_FAN2] = "fan2";
}
void BoardCaptain::initTemperatureSensors (void) {

  ntc1 = new NTC ();
  ntc2 = new NTC ();
  ntc_int = new NTC ();
  
  ntc1->init_103AT2(ADC_TEMP_1, REF_RES, 10);
  ntc2->init_NCP15XW(ADC_TEMP_2, REF_RES, 10);
  ntc_int->init_NCP15XW(ADC_TEMP_INTERN, 10500, 10);   // diffrent voltage 
}
void BoardCaptain::run_system (void) {
 
  ntc1->measureTemperature();
  ntc2->measureTemperature();
  ntc_int->measureTemperature();
  this->senseFans ();


   if (millis() - previousMillis > 10) {
    previousMillis = millis();   // aktuelle Zeit abspeichern
    dcdc1.smbus_transfer();
    dcdc2.smbus_transfer();
    dcdc3.smbus_transfer();
  }

  //Serial.println(sense_input_voltage());
  if (sense_enable_input()) {
    state_led (BC_OK);
    //dcdc2.turnOn();
    //dcdc2.configure ();
  }
  else {
    state_led (BC_ERROR);
    dcdc2.turn(false);
  } 
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
bool BoardCaptain::turn_on_off (int8_t psu, bool on_off) {
  bool error = false;
  
  switch (psu) {
      case 0 : dcdc1.turn (on_off); break;
      case 1 : dcdc2.turn (on_off); break;
      case 2 : dcdc3.turn (on_off); break;
      case -1 : dcdc1.turn (on_off); 
                dcdc2.turn (on_off);
                dcdc3.turn (on_off);
        break;
      default : error = true; break;
    }
    return error;
}
void BoardCaptain::listParameter (int8_t psu) {
  switch (psu) {
      case 0 : dcdc1.printAsJSON (); break;
      case 1 : dcdc2.printAsJSON (); break;
      case 2 : dcdc3.printAsJSON (); break;
      case -1: this->printAsJSON ();
               dcdc1.printAsJSON ();
               dcdc2.printAsJSON ();
               dcdc3.printAsJSON ();
      break;
    } 
}
void BoardCaptain::printAsJSON (void) {
  
  PRINT_JSTART
    PRINT_JSON_NAME_ID("psu", -1) 
    PRINT_JSTART
    for (uint8_t i=0; i!=DATA_ARRAY_SIZE;i++) {
      PRINT_JSON_NAME(data_name[i])
      Serial.print (":");
      Serial.print (data_array[i]);
      if (i != (DATA_ARRAY_SIZE-1))
        Serial.print (",");
    }
    PRINT_JSTOP
  PRINT_JSTOP
  Serial.println ("");

}
// +++++++++++++++++++++++++++++++ +++++++++++++++++++++++++++++++ +++++++++++++++++++++++++++++++
void BoardCaptain::initFans (void) {
  fan1 = new FanController(FAN_TACH_1, SENSOR_THRESHOLD, FAN_DRIVE_1);
  fan2 = new FanController(FAN_TACH_2, SENSOR_THRESHOLD, FAN_DRIVE_2);
  
  fan1->begin();
  fan2->begin();

  setFanSpeed (0,0);
  setFanSpeed (1,0);
}
void BoardCaptain::senseFans (void) {
  unsigned int rpms1 = fan1->getSpeed(); // Send the command to get RPM
  unsigned int rpms2 = fan2->getSpeed(); // Send the command to get RPM
}
void BoardCaptain::setFanSpeed (uint8_t fan, uint8_t fanspeed) {
  if (fanspeed <= 100) {    
    switch (fan) {
      case 0: fan1->setDutyCycle(fanspeed);
      case 1: fan2->setDutyCycle(fanspeed);
    }
  }
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
float BoardCaptain::getTempFan (uint8_t fan) {
  if (fan == 1) return ntc1->getTemperature();
  else if (fan == 2) return ntc2->getTemperature();
  else return -1;
}




