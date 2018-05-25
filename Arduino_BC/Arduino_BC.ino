

#include "BoardCaptain.h"

/* Project: Arduino BC (Board-Captain) 
 * @athor: Nils Minor
 * @date:  20.02.2018
 * 
 * @brief Arduino based processing unit for the following tasks:
 *   - control and monitor ZL2102 DCDC converters via SM BUS
 *
 *
 *
 *
 * Zum Aufspielen des Bootloaders
 * SMART PSU
 *        OL
 * Braun (X)(X) Gelb
 * Weiß  (X)(X) Grün
 * Rot   (X)(X) Grau
 * 
 * 
 * Arduino 
 * 
 * Braun (X)(X) Rot
 * Weiß  (X)(X) Grün
 *       (X)(X) Grau
 * Reset Gelb Pin 10
 * 
 */

// IO Defines
BoardCaptain BC;

void setup() {
  Serial.begin (115200);    // Init Serial interface 
   //BC.smbus_test();
}

void loop() {
 
  BC.run_system ();
 
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++







