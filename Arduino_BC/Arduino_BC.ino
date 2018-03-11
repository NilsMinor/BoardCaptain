#include <Wire.h>

#include "BoardCaptain.h"



/* Project: Arduino BC (Board-Captain) 
 * @athor: Nils Minor
 * @date:  20.02.2018
 * 
 * @brief Arduino based processing unit for the following tasks:
 *   - control and monitor ZL2102 DCDC converters via SM BUS
 *
 */




// IO Defines
BoardCaptain BC;

void setup() {

  Serial.begin (115200);
  Serial.println("CLI started - v1.0.0");
}

void loop() {
  BC.cli_update();
}
