

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
  Serial.println(argc);
  if (!arg_check(argc, 2)) {
      Serial.println(argv[1]);
      if (argv[1] == "0.8")       {BC.set_vadj(V_0V8); Serial.println("0.8V");}
      else if (argv[1] == "1.2")  {BC.set_vadj(V_1V2); Serial.println("1.2V");}
      else return 10;
  
      return 0;
  }
  return 10;
}





