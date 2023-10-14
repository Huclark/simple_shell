#include "shell.h"

/**
* put_char - Prints a char character to standard output
* @ch: The character to print
* Return: 1 on success and -1 on failure
*/

int put_char(char ch)
{
	int ret_value = write(1, &ch, 1);

	return (ret_value);
}


/**
 * cust_puts - replicates the puts function
 * @string: string input to print
*/

void cust_puts(char *string)
{
	int idx = 0;

	if (string == NULL)
		return;
	while (string[idx] != '\0')
	{
		put_char(string[idx]);
		idx += 1;
	}
}


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
	cust_puts(prog_name);
	cust_puts(": ");
	put_char(line_no + '0');
	cust_puts(": ");
	cust_puts(argv_tkn[0]);
	cust_puts(": ");
	cust_puts(error_msg);
	put_char('\n');
}


/**
 * error_output - Prints the same error output as sh (/bin/sh) for "exit"
 * @prog_name: Program name
 * @argv_tkn: Null-terminated array of command and parameters
 * @error_msg: The error message string
 * @line_no: Number of lines processed
*/
void exit_error_output(char *prog_name, char **argv_tkn,
					char *error_msg, int line_no)
{
	cust_puts(prog_name);
	cust_puts(": ");
	put_char(line_no + '0');
	cust_puts(": ");
	cust_puts(argv_tkn[0]);
	cust_puts(": ");
	cust_puts(error_msg);
	cust_puts(": ");
	cust_puts(argv_tkn[1]);
	put_char('\n');
}

