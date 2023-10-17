#include "shell.h"

/**
 * error_output - Prints the same error output as sh (/bin/sh)
 * @prog_name: Program name
 * @argv_tkn: Null-terminated array of command and parameters
 * @error_msg: The error message string
 * @line_no: Number of lines processed
*/
void error_output(char *prog_name, char **argv_tkn,
					char *error_msg, int line_no)
{
	e_cust_puts(prog_name);
	e_cust_puts(": ");
	print_numbers(line_no, STDERR_FILENO);
	e_cust_puts(": ");
	e_cust_puts(argv_tkn[0]);
	e_cust_puts(": ");
	e_cust_puts(error_msg);
	e_put_char('\n');
}


/**
 * exit_error_output - Prints the same error output as sh (/bin/sh) for "exit"
 * @prog_name: Program name
 * @argv_tkn: Null-terminated array of command and parameters
 * @error_msg: The error message string
 * @line_no: Number of lines processed
*/
void exit_error_output(char *prog_name, char **argv_tkn,
					char *error_msg, int line_no)
{
	e_cust_puts(prog_name);
	e_cust_puts(": ");
	print_numbers(line_no, STDERR_FILENO);
	e_cust_puts(": ");
	e_cust_puts(argv_tkn[0]);
	e_cust_puts(": ");
	e_cust_puts(error_msg);
	e_cust_puts(": ");
	e_cust_puts(argv_tkn[1]);
	e_put_char('\n');
}


/**
 * cd_error_output - Prints the same error output as sh (/bin/sh) for "exit"
 * @prog_name: Program name
 * @argv_tkn: Null-terminated array of command and parameters
 * @error_msg: The error message string
 * @line_no: Number of lines processed
*/
void cd_error_output(char *prog_name, char **argv_tkn,
					char *error_msg, int line_no)
{
	e_cust_puts(prog_name);
	e_cust_puts(": ");
	print_numbers(line_no, STDERR_FILENO);
	e_cust_puts(": ");
	e_cust_puts(argv_tkn[0]);
	e_cust_puts(": ");
	e_cust_puts(error_msg);
	e_put_char(' ');
	e_cust_puts(argv_tkn[1]);
	e_put_char('\n');
}

