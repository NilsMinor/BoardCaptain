

/* This file acts as wrapper class for the communication interface of the BoardCaptain controller.
 * By adding a wrapper class it is easier to change a shell or cli class below. 
 *
 * In the moment the cli interface is based on shell.h from https://github.com/geekfactory/Shell
 */
#ifndef _CLI_H_
#define _CLI_H_

#include "BoardCaptain.h"
#include <Shell.h>


class BC_CLI  {
  public:
    BC_CLI ( );
    void register_commands (void);
    void run_shell_interface (void);
    void register_bc_command (const char* str, float (*getter),void (*setter)(float));
  private:
    static int command_test(int argc, char** argv);
    
    
};




#endif
