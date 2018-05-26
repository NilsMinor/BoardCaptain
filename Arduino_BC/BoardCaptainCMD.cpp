

#include "BoardCaptain.h"


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
/*

static int  shell_reader(char * data) {
  // Wrapper for Serial.read() method
  if (Serial.available()) {
    *data = Serial.read();
    return 1;
  }
  return 0;
}
static void shell_writer(char data) {
  // Wrapper for Serial.write() method
  Serial.write(data);
}

void BoardCaptain::run_shell_interface (void) {
  shell.shell_task();
}



bool BoardCaptain::setter_helper (char** argv) {
  
  int PSU = String(argv[2]).toInt ();
  float value = String (argv[3]).toFloat();
  bool error = true;
  
  if (argv[1] == "VOUT") {
    switch (PSU) {
     // case 0 : error = dcdc1.setVout (value); break;
     // case 1 : error = dcdc2.setVout (value); break;
     // case 2 : error = dcdc3.setVout (value); break;
      //*processed = true;  // command was processed
      return error;

      Serial.print ("PSU : ");Serial.print (PSU);
      Serial.print (" Voltage : ");Serial.print (value);
    }
  }
  return false;
}
int BoardCaptain::command_set (int argc, char** argv) {
 bool processed = false;
 bool error = true;

  if (argc == 4) {
    if (argv[1] == "VOUT") {
       //error = setter_helper (argv);
       //dcdc1.setVout (3.3);
    }
    return SHELL_RET_SUCCESS;
  }
  
  return SHELL_RET_FAILURE;
}

void BoardCaptain::test (void) {
  Serial.println("Hello callback");
}
static int command_get (int argc, char** argv) {
  
}

void BoardCaptain::init_shell (void) {
  shell.shell_init(shell_reader, shell_writer, 0); 
  shell.shell_calback (command_get);
  //shell.shell_register2(command_get, PSTR("set"));
  //shell_register(command_get, PSTR("get"));
}
*/


