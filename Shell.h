/*  Command Line Interface (Command Shell) for microcontrollers.
  Copyright (C) 2014 Jesus Ruben Santa Anna Zamudio.

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
  Author website: http://www.geekfactory.mx
  Author e-mail: ruben at geekfactory dot mx
 */
#ifndef SHELL_H
#define SHELL_H
/*-------------------------------------------------------------*
 *    Includes and dependencies     *
 *-------------------------------------------------------------*/
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>

#include <Arduino.h>


/*-------------------------------------------------------------*
 *    Library Configuration       *
 *-------------------------------------------------------------*/

/**
 * You can configure several operation parameters of the shell library here
 */

#if !defined(CONFIG_SHELL_MAX_COMMANDS)
/**
 * Defines the maximum number of commands that can be registered
 */
#define CONFIG_SHELL_MAX_COMMANDS   5
#endif
#if !defined(CONFIG_SHELL_MAX_INPUT)
/**
 * Defines the maximum characters that the input buffer can accept
 */
#define CONFIG_SHELL_MAX_INPUT      70
#endif
#if !defined(CONFIG_SHELL_MAX_COMMAND_ARGS)
/**
 * Configures the maximum number of arguments per command that can be accepted
 */
#define CONFIG_SHELL_MAX_COMMAND_ARGS   10
#endif

#if !defined(CONFIG_SHELL_FMT_BUFFER)
/**
 * Defines the buffer for formatted string output from program memory.
 * THIS SETTING IS USED ONLY FOR ARDUINO BOARDS
 */
#define CONFIG_SHELL_FMT_BUFFER     70
#endif

/**
 * End of user configurable parameters, do not touch anything below this line
 */ 

/*-------------------------------------------------------------*
 *    Macros & definitions        *
 *-------------------------------------------------------------*/
#define SHELL_ASCII_NUL       0x00
#define SHELL_ASCII_BEL       0x07
#define SHELL_ASCII_BS        0x08
#define SHELL_ASCII_HT        0x09
#define SHELL_ASCII_LF        0x0A
#define SHELL_ASCII_CR        0x0D
#define SHELL_ASCII_ESC       0x1B
#define SHELL_ASCII_DEL       0x7F
#define SHELL_ASCII_US        0x1F
#define SHELL_ASCII_SP        0x20
#define SHELL_VT100_ARROWUP     'A'
#define SHELL_VT100_ARROWDOWN     'B'
#define SHELL_VT100_ARROWRIGHT      'C'
#define SHELL_VT100_ARROWLEFT     'D'

#define SHELL_RET_SUCCESS     0
#define SHELL_RET_FAILURE     1
#define SHELL_RET_IOPENDING     -1

#define SHELL_VERSION_STRING      "1.1.0"

/*-------------------------------------------------------------*
 *    Typedefs enums & structs      *
 *-------------------------------------------------------------*/

typedef int (*shell_program_t) (int, char **);


typedef void (*shell_writer_t) (char);
typedef int (*shell_reader_t) (char *);

enum shell_errors {
  /** There are missing arguments for the command */
  E_SHELL_ERR_ARGCOUNT = 0,
  /** The program received an argument that is out of range */
  E_SHELL_ERR_OUTOFRANGE,
  /** The program received an argument with a value different than expected */
  E_SHELL_ERR_VALUE,
  /** Invalid action requested for the current state */
  E_SHELL_ERR_ACTION,
  /** Cannot parse the user input */
  E_SHELL_ERR_PARSE,
  /** Cannot access storage device or memory device */
  E_SHELL_ERR_STORAGE,
  /** IO device error caused program interruption */
  E_SHELL_ERR_IO,
  /** Other kinds of errors */
  E_SHELL_ERROR_UNKNOWN,
};

/**
 * This structure holds the data for every command registered on the shell
 */
struct shell_command_entry {
  shell_program_t shell_program;
  const char * shell_command_string;
};


class Shell {
  public:
    bool shell_init(shell_reader_t reader, shell_writer_t writer, char * msg);
    bool shell_register(shell_program_t program, const char * string);
    bool shell_register2(int *program (int, char **), const char * string);
    void shell_unregister_all();
    void shell_putc(char c);
    void shell_print(const char * string);
    void shell_println(const char * string);
    void shell_printf(const char * fmt, ...);
    void shell_print_commands();
    void shell_print_error(int error, const char * field);
    void shell_task();
    void shell_print_pm(const char * string);
    void shell_println_pm(const char * string);
    void shell_printf_pm(const char * fmt, ...);
    void shell_calback (void(*fptr)(void));
  private:
    int shell_parse(char * buf, char ** argv, unsigned short maxargs);
    void shell_process_escape(int argc, char ** argv);
    void shell_prompt();
    void shell_format(const char * fmt, va_list va);
    void uli2a(unsigned long int num, unsigned int base, int uc, char * bf);
    void li2a(long num, char * bf);
    void ui2a(unsigned int num, unsigned int base, int uc, char * bf);
    void i2a(int num, char * bf);
    int a2d(char ch);
    char a2i(char ch, const char** src, int base, int* nump);
    void putchw(int n, char z, char* bf);
};
  

#endif
// End of Header file

