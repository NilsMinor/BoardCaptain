

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
#include <Shell.h>
// IO Defines
BoardCaptain* BC;

void setup() {
  BC = new BoardCaptain ();
  Serial.begin (115200);      // Init Serial interface 
  analogReference(EXTERNAL);  // 2.5V external voltage reference

  shell_init(shell_reader, shell_writer, 0);

  // Add commands to the shell
  shell_register(command_set, PSTR("set"));
  shell_register(command_get, PSTR("get"));
}

void loop() {
 
  BC->run_system ();
  shell_task();
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/* PSU 0 DCDC0
 * PSU 1 DCDC1 
 * PSU 2 DCDC2
 * PSU 3 Vadj
 * 
 * COMMAND  Parameter    PSU       Value
 * set      VOUT         [0-3]     [PSU 0,1,2] =  0 | 0.5 - 5
 * 
 *
 *
 *
 */
 
int shell_reader(char * data) {
  // Wrapper for Serial.read() method
  if (Serial.available()) {
    *data = Serial.read();
    return 1;
  }
  return 0;
}
void shell_writer(char data){
  // Wrapper for Serial.write() method
  Serial.write(data);
}

bool setter_helper (char** argv) {
  
  int psu = String(argv[2]).toInt ();
  float value = String (argv[3]).toFloat();
  bool error = true;
  
  if (!strcmp(argv[1], (const char *) "VOUT")) {
    error = BC->setVout (psu, value);
  }
  return false;
}
int command_set (int argc, char** argv) {
 bool processed = false;
 bool error = true;

  if (argc == 4) {
     error = setter_helper (argv);
     if (!error)
      return SHELL_RET_SUCCESS;
  }
  return SHELL_RET_FAILURE;
}


static int command_get (int argc, char** argv) {
  
}





