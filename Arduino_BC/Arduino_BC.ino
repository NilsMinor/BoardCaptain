

#include "BoardCaptain.h"



/* Project: Arduino BC (Board-Captain) 
 * @athor: Nils Minor
 * @date:  20.02.2018
 * 
 * @brief Arduino based processing unit for the following tasks:
 *   - control and monitor ZL2102 DCDC converters via SM BUS
 *
 */

CLI_COMMAND(setVadj);
CLI_COMMAND(helpFunc);

// IO Defines
BoardCaptain BC;

void setup() {
  Serial.begin (115200);    // Init Serial interface
  CLI.setDefaultPrompt("> ");
    
  CLI.addCommand("setVadj", setVadj);
  CLI.addCommand("help", helpFunc);

  CLI.addClient(Serial);
}

void loop() {

 CLI.process(); 
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

bool arg_check (uint8_t args, uint8_t argc) {
  if (args != argc) {
    Serial.println("ARG ERROR");
    return false;
  }
  return true;
}

CLI_COMMAND(helpFunc) {
    dev->println("add <number 1> <number 2> - Add two numbers together");
    return 0;
}

CLI_COMMAND(setVadj) {
  if (!arg_check(argc, 2)) {
      switch (argv[1]) {
        case ("0V8"): dev->println("OK set Vadj 0.8V");
                      bc.set_vadj(V_0V8);
        break;
        case ("1V2"): dev->println("OK set Vadj 1.2V");
                      bc.set_vadj(V_1V2);
        break;
        
      }
      
    
        
        return 0;
  }
  return 10;
}





