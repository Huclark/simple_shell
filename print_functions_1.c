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
 * e_put_char - Prints a char character to standard error
 * @ch: The character to print
 * Return: 1 on success and -1 on failure
 */
int e_put_char(char ch)
{
	int ret_value = write(2, &ch, 1);

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
 * e_cust_puts - replicates the puts function
 * @string: string input to print
 */

void e_cust_puts(char *string)
{
	int idx = 0;

	if (string == NULL)
		return;
	while (string[idx] != '\0')
	{
		e_put_char(string[idx]);
		idx += 1;
	}
}


/**
 * print_numbers - function prints a decimal (integer) number (base 10)
 * @num_to_print: the num_to_print
 * @file_desc: file stream
 * Return: number of characters printed
 */
int print_numbers(int num_to_print, int file_desc)
{
	int idx, __counter = 0;

	unsigned int absolute, curr_num;

	int (*putchar_ptr)(char) = put_char;

	if (file_desc == STDERR_FILENO)
		putchar_ptr = e_put_char;

	if (num_to_print < 0)
	{
		absolute = -num_to_print;
		putchar_ptr('-');
		__counter++;
	}
	else
		absolute = num_to_print;
	curr_num = absolute;
	for (idx = 1000000000; idx > 1; idx /= 10)
	{
		if (absolute / idx)
		{
			putchar_ptr('0' + curr_num / idx);
			__counter++;
		}
		curr_num %= idx;
	}
	putchar_ptr('0' + curr_num);
	__counter++;

	return (__counter);
}


