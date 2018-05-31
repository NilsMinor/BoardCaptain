

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
 #define PROCESSED_FLAG   0x01
#include <Shell.h>
// IO Defines
BoardCaptain* BC;

uint8_t processed = 0x00;
bool error = false;

void setup() {
  BC = new BoardCaptain ();
  Serial.begin (115200);      // Init Serial interface 
  analogReference(EXTERNAL);  // 2.5V external voltage reference

  shell_init(shell_reader, shell_writer, 0);

  // Add commands to the shell
  shell_register(command_set, PSTR("set"));
  shell_register(command_get, PSTR("get"));
  shell_register(command_list, PSTR("list"));
  shell_register(command_turn, PSTR("turn"));
}
void loop() {
 
  BC->run_system ();
  shell_task();
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/* PSU -1 all 
 * PSU 0 DCDC0
 * PSU 1 DCDC1 
 * PSU 2 DCDC2
 * PSU 3 Vadj
 * 
 * 
 * COMMAND  Parameter     PSU       Value
 * set      vout          [0-3]     [PSU 0,1,2] =  0 | 0.5 - 5
 *          fan           [0-1]     0-100
 *          
 *            
 * get      vout          [0-3]     output voltage in [V]
 *          vin           [0-3]     input voltage in  [V]
 *          iout          [0-3]     output current in [A]
 *          pout          [0-3]     output power in   [W]  
 *
 * list                   [0-3]              
 * 
 * turn     on/off        [0-3]     -1 will turn off all          
 *
 */
 
int shell_reader(char * data) {
  if (Serial.available()) {
    *data = Serial.read();
    return 1;
  }
  return 0;
}
void shell_writer(char data){
  Serial.write(data);
}
static bool checkArgument (const char * str1, const char * str2) { 
  return (!strcmp(str1, str2));
}
bool setter_helper (char** argv, uint8_t *proc) {
  
  int psu = String(argv[2]).toInt ();
  error = false;
  
  if (checkArgument(argv[1],"vout" ) ) {
    
    error = BC->setVout (psu, String (argv[3]).toFloat());
    *proc = PROCESSED_FLAG;
  }
  else if (checkArgument(argv[1], "fan" ) ) {
    BC->setFanSpeed (psu, (uint8_t) String(argv[3]).toInt ());
    *proc = PROCESSED_FLAG;
  }
  return false;
}
float getter_helper (char** argv, uint8_t *proc) {
  
  int psu = String(argv[2]).toInt ();
  float value = 0;
  
  if (checkArgument(argv[1], "vout" ) ) {
    value = BC->getVout (psu); 
    *proc = PROCESSED_FLAG;
  }
  else if (checkArgument (argv[1],"vin") ) {
    value = BC->getVin (psu); 
    *proc = PROCESSED_FLAG;  
  }
  else if (checkArgument (argv[1],"iout") ) {
    value = BC->getIout (psu); 
    *proc = PROCESSED_FLAG;
  }
  else if (checkArgument (argv[1],"pout") ) {
    value = BC->getPout (psu); 
    *proc = PROCESSED_FLAG;
  }
  
  return value;
}
static int command_set (int argc, char** argv) {
 processed = 0;
 error = false;

  if (argc == 4) {
     error = setter_helper (argv, &processed);
     if (!error && processed == PROCESSED_FLAG) 
        return SHELL_RET_SUCCESS;
  }
  return SHELL_RET_FAILURE;
}
static int command_get (int argc, char** argv) {
 processed = 0;
 float retval = 0;
  if (argc == 3) {
     retval = getter_helper (argv, &processed);
     shell_println (String(retval).c_str());
     
     if (retval != -1 && processed == PROCESSED_FLAG) 
        return SHELL_RET_SUCCESS;
  }
  return SHELL_RET_FAILURE;
}
static int command_list (int argc, char** argv) {
  error = false;
  int psu = String(argv[1]).toInt ();
  
  if (argc == 2) {
      BC->listParameter (psu);
         
     if (!error && processed == PROCESSED_FLAG) 
        return SHELL_RET_SUCCESS;
  }
  return SHELL_RET_FAILURE;
}
static int command_turn (int argc, char** argv)  {
  error = false;
  int psu = String(argv[2]).toInt ();
  if (argc == 3) {  
    if (checkArgument(argv[1],"on" ) ) {
      error = BC->turn_on_off (psu, true);
    }
    else if (checkArgument(argv[1],"off" ) ) {
      error = BC->turn_on_off (psu, false);
    }
     
     if (!error && processed == PROCESSED_FLAG) 
        return SHELL_RET_SUCCESS;
  }
  return SHELL_RET_FAILURE;
}


