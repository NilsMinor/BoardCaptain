

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
 *       (X)(X)
 * Reset Gelb Pin 10
 * 
 */

CLI_COMMAND(setVadj);
CLI_COMMAND(setV);
CLI_COMMAND(getV);
CLI_COMMAND(helpFunc);

// IO Defines
BoardCaptain BC;

void setup() {
  Serial.begin (115200);    // Init Serial interface
  CLI.setDefaultPrompt("> ");
    
  CLI.addCommand("setV", setVadj);
  CLI.addCommand("help", helpFunc);

  CLI.addClient(Serial);
}

void loop() {

 //CLI.process(); 
  
  BC.state_led (BC_ERROR);
  delay(200);
  BC.state_led (BC_OK);
  delay(200);
  BC.search_smbus_devices();
 
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
    dev->println("PSU 0 = Input");
    dev->println("PSU 1,2,3,4 = Output 1,2,3,4");
    dev->println("[return value] - cmd   - < value list >");
    dev->println("[ void ]       - setV  - < PSU > < Voltage >");
    dev->println("[ float ]      - getV  - < PSU >");
    dev->println("[ float ]      - getI  - < PSU >");
    dev->println("[ float ]      - getP  - < PSU >");
    return 0;
}
CLI_COMMAND(setVadj) {
  
  for (int i=0;i!=argc;i++)
      Serial.println(argv[i]);
      
  if (arg_check(argc, 3)) {
      if (argv[1] == "0") {
        Serial.println ("Arg 1 gechecked");
        if (argv[2] == "0.8V")       BC.set_vadj(V_0V8); 
        else if (argv[2] == "1.2V")  BC.set_vadj(V_1V2);
        else if (argv[2] == "1.25V") BC.set_vadj(V_1V25);
        else if (argv[2] == "1.5V")  BC.set_vadj(V_1V5);
        else if (argv[2] == "1.8V")  BC.set_vadj(V_1V8);
        else if (argv[2] == "2.5V")  BC.set_vadj(V_2V5);
        else if (argv[2] == "3.3V")  BC.set_vadj(V_3V3);
        else return 0;
      }
      return 10;
  }
  return 10;
}





