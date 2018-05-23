
#include "CLI.h"


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

void BC_CLI::run_shell_interface (void) {
  shell_task();
}
static void BC_CLI::register_commands (void) {
  shell_register(command_test, PSTR("test"));
}

static void BC_CLI::register_bc_command (const char* str, float (*getter),void (*setter)(float)) {
  shell_register(command_test, str);
  
}

BC_CLI::BC_CLI ( ) {
  
  shell_init(shell_reader, shell_writer, 0);
}

int BC_CLI::command_test(int argc, char** argv){
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

/*CLI_COMMAND(helpFunc) {
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
}*/
