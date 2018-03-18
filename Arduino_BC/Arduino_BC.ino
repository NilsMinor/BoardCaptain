

#include "BoardCaptain.h"



/* Project: Arduino BC (Board-Captain) 
 * @athor: Nils Minor
 * @date:  20.02.2018
 * 
 * @brief Arduino based processing unit for the following tasks:
 *   - control and monitor ZL2102 DCDC converters via SM BUS
 *
 */




/**
 * PSU 0 = Input
 * PSU 1,2,3,4 = Output 1,2,3,4
 * T-Source = 0 (internal)
 *            1,2 (Fan1, Fan2)
 * 
 * [return value] - cmd   - < value list >
 * [ void ]       - setV  - < PSU > < Voltage >
 * [ float ]      - getV  - < PSU >
 * [ float ]      - getI  - < PSU > 
 * [ float ]      - getP  - < PSU >
 * [ float ]      - getT  - < T-Source >
 *
 *
 *
 *
 **/

CLI_COMMAND(setVadj);
CLI_COMMAND(setV);
CLI_COMMAND(getV);
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
      if (argv[1] == "0.8V")       BC.set_vadj(V_0V8); 
      else if (argv[1] == "1.2V")  BC.set_vadj(V_1V2);
      else if (argv[1] == "1.25V") BC.set_vadj(V_1V25);
      else if (argv[1] == "1.5V")  BC.set_vadj(V_1V5);
      else if (argv[1] == "1.8V")  BC.set_vadj(V_1V8);
      else if (argv[1] == "2.5V")  BC.set_vadj(V_2V5);
      else if (argv[1] == "3.3V")  BC.set_vadj(V_3V3);
      else return 10;
  
      return 0;
  }
  return 10;
}





