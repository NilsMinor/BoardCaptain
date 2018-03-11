
#include "BoardCaptain.h"



// Initialize IOs and Communication ports
BoardCaptain::BoardCaptain (void) {

  pinMode(OUT_SET_VADJ_VS0, OUTPUT);
  pinMode(OUT_SET_VADJ_VS1, OUTPUT);
  pinMode(OUT_SET_VADJ_VS2, OUTPUT);
  pinMode(OUT_EN_VADJ_1,    OUTPUT);
  digitalWrite (OUT_EN_VADJ_1, LOW); // disable adjustable voltage controller
  
}

static void error_handler (const char *err_msg) {
  Serial.print ("Error: ");
  Serial.println(err_msg);
}



static void vadj_set_outputs (uint8_t VS2, uint8_t VS1, uint8_t VS0) {
  digitalWrite (OUT_SET_VADJ_VS0, VS0);
  digitalWrite (OUT_SET_VADJ_VS0, VS1);
  digitalWrite (OUT_SET_VADJ_VS2, VS2);   
  
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
    break;
    default: error_handler("Vadj error, not implemented");
    break;
  }
  
}

