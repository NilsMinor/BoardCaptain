
#include "BoardCaptain.h"

#define ZL2102_ADDR_1   0x20
#define ZL2102_ADDR_2   0x21
#define ZL2102_ADDR_3   0x22

// Initialize IOs and Communication ports
BoardCaptain::BoardCaptain (void) {

  pinMode (OUT_nLED_RG, OUTPUT);

  pinMode(OUT_SET_VADJ_VS0, OUTPUT);
  pinMode(OUT_SET_VADJ_VS1, OUTPUT);
  pinMode(OUT_SET_VADJ_VS2, OUTPUT);
  pinMode(OUT_EN_VADJ_1,    OUTPUT);
  enable_vadj (false);                // disable adjustable voltage controller

  smbus = new LT_SMBusNoPec();
  pmbus = new LT_PMBus(smbus);

  dcdc1.init (pmbus, smbus, ZL2102_ADDR_2);

  initTemperatureSensors( );

  pinMode (SYSTEM_EN, INPUT);
  sense_enable_input ( );      // update

  bc_cli = new BC_CLI ();
  bc_cli->register_commands(); // register commands
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
  bc_cli->run_shell_interface ();   // run cli interface

  ntc1->measureTemperature();
  ntc2->measureTemperature();

  delay (100);
  
  if (sense_enable_input()) {
    state_led (BC_OK);
    dcdc1.turnOn();
  }
  else {
    state_led (BC_ERROR);
    dcdc1.turnOff();
  }
 
}
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
// Config adjustable voltage
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
double BoardCaptain::getTempIntern (void) {
  return ntc_int->getTemperature();
}

float BoardCaptain::getTempFan1 (void) {
  return ntc1->getTemperature();
}
float BoardCaptain::getTempFan2 (void) {
  return ntc1->getTemperature();
}



