#include "BoardCaptain.h"


static int shell_reader(char * data) {
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
  shell_task();
}

void BoardCaptain::register_bc_command (const char* str, float (*getter),void (*setter)(float)) {
  shell_register(command_test, str);
}

void BoardCaptain::init_shell (void) {
  shell_init(shell_reader, shell_writer, 0);
  shell_register(command_test, PSTR("test"));
  //register_bc_command ("hallo",NULL,NULL);
}
int BoardCaptain::command_test(int argc, char** argv){
  int i;
  shell_printf("Received %d arguments for test command\r\n",argc);

  // Print each argument with string lenghts
  for(i=0; i<argc; i++)
  {
    // Print formatted text to terminal
    shell_printf("%d - \"%s\" [len:%d]\r\n", i, argv[i], strlen(argv[i]) );
  }

  return SHELL_RET_SUCCESS;
}
