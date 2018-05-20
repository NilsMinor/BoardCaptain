
#include "BoardCaptain.h"


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
    case (V_3V3): vadj_set_outputs(LOW,LOW,LOW);  
    break;
    case (V_2V5): vadj_set_outputs(LOW,LOW,HIGH);
    break;
    case (V_1V8): vadj_set_outputs(LOW,HIGH,LOW);
    break;
    case (V_1V5): vadj_set_outputs(LOW,HIGH,HIGH);
    break;
    case (V_1V25): vadj_set_outputs(HIGH,LOW,LOW);
    break;
    case (V_1V2): vadj_set_outputs(HIGH,LOW,HIGH);
    break;
    case (V_0V8): vadj_set_outputs(HIGH,HIGH,LOW);
    Serial.println("set Vadj to 0.8V");
    break;
    default: error_handler("Vadj error, not implemented");
    break;
  }
}
float BoardCaptain::get_parameter (uint8_t psu, PARAMETER parameter) {


  
}
void  BoardCaptain::state_led (LED_STATE state) {
  if (state == BC_ERROR)    digitalWrite (OUT_nLED_RG, LOW);
  else if (state == BC_OK)  digitalWrite (OUT_nLED_RG, HIGH); 
  
}



