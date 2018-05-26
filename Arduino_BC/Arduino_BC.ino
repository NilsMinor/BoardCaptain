

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
  shell_register(command_test, PSTR("test"));
}

void loop() {
 
  BC->run_system ();
  shell_task();
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int command_test(int argc, char** argv)
{
  int i;

  shell_println("-----------------------------------------------");
  shell_println("SHELL DEBUG / TEST UTILITY");
  shell_println("-----------------------------------------------");
  shell_println("");
  shell_printf("Received %d arguments for test command\r\n",argc);

  // Print each argument with string lenghts
  for(i=0; i<argc; i++)
  {
    // Print formatted text to terminal
    shell_printf("%d - \"%s\" [len:%d]\r\n", i, argv[i], strlen(argv[i]) );
  }

  return SHELL_RET_SUCCESS;
}

/**
 * Function to read data from serial port
 * Functions to read from physical media should use this prototype:
 * int my_reader_function(char * data)
 */
int shell_reader(char * data)
{
  // Wrapper for Serial.read() method
  if (Serial.available()) {
    *data = Serial.read();
    return 1;
  }
  return 0;
}

/**
 * Function to write data to serial port
 * Functions to write to physical media should use this prototype:
 * void my_writer_function(char data)
 */
void shell_writer(char data)
{
  // Wrapper for Serial.write() method
  Serial.write(data);
}





