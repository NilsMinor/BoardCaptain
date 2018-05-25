

/* This file acts as wrapper class for the communication interface of the BoardCaptain controller.
 * By adding a wrapper class it is easier to change a shell or cli class below. 
 *
 * In the moment the cli interface is based on shell.h from https://github.com/geekfactory/Shell
 */
#ifndef _CLI_H_
#define _CLI_H_

#include "BoardCaptain.h"
#include <Shell.h>



/* PSU 0 DCDC0
 * PSU 1 DCDC1 
 * PSU 2 DCDC2
 * PSU 3 Vadj
 * 
 * COMMAND  Parameter  PSU     Value
 * set      V         [0-3]     [0-2] 0| 0.5-5
 *
 *
 *
 *
 */
 
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
