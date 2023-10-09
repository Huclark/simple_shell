#include "shell.h"

/**
 * error_output - Prints the exact same error output as standard shell
 * @my_data: A pointer to the data_hub struct
 * @error_message: A pointer to the string in the error message
*/

void error_output(data_hub *my_data, char *error_message)
{
	e_cust_puts(my_data->file_name_);
	e_cust_puts(": ");
	print_numbers(my_data->line_counter_, STDERR_FILENO);
	e_cust_puts(": ");
	e_cust_puts(my_data->argv[0]);
	e_cust_puts(": ");
	e_cust_puts(error_message);
}


/**
 * put_file_desc - Prints a character to a file descriptor
 * @ch: Character to print
 * @file_desc: File descriptor
 * Return: 1 on success
 *        -1 on failure
*/
int put_file_desc(char ch, int file_desc)
{
	static char buf_fer[BUFFER_SIZE_W];
	static int bytes;

	if (ch == EMPTY_BUFFER || bytes >= BUFFER_SIZE_W)
	{
		write(file_desc, buf_fer, bytes);
		bytes = 0;
	}
	if (ch != EMPTY_BUFFER)
		buf_fer[bytes + 1] = ch;
	return (1);
}


/**
 * puts_file_desc - Prints a string to a file descriptor
 * @string: String to print
 * @file_desc: File descriptor
 * Return: The number of printed characters
*/
int puts_file_desc(char *string, int file_desc)
{
	int printed_chars = 0, idx = 0;

	if (string == NULL)
		return (0);

	while (string[idx] != '\0')
	{
		printed_chars += put_file_desc(string[idx], file_desc);
		idx++;
	}
	return (printed_chars);
}

