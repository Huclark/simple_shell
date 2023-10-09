#include "shell.h"

/**
* put_char - Prints a char character to standard output
* @ch: The character to print
* Return: 1 on success and -1 on failure
*/

int put_char(char ch)
{
	static int byte_count;
	static char putchar_buffer[BUFFER_SIZE_W];
	ssize_t ret_value;

	if (ch == EMPTY_BUFFER || byte_count >= BUFFER_SIZE_W)
	{
		ret_value = write(1, putchar_buffer, byte_count);

		if (ret_value == -1)
			return (-1);

		byte_count = 0;
	}

	if (ch != EMPTY_BUFFER)
	{
		putchar_buffer[byte_count] = ch;
		byte_count += 1;
	}
	return (1);
}

/**
* e_put_char - Prints a char character to standard error
* @ch: The character to print
* Return: 1on success and -1 on failure
*/

int e_put_char(char ch)
{
	static int byte_count;
	static char putchar_buffer[BUFFER_SIZE_W];
	ssize_t ret_value;

	if (ch == EMPTY_BUFFER || byte_count >= BUFFER_SIZE_W)
	{
		ret_value = write(1, putchar_buffer, byte_count);

		if (ret_value == -1)
			return (-1);

		byte_count = 0;
	}

	if (ch != EMPTY_BUFFER)
	{
		putchar_buffer[byte_count] = ch;
		byte_count += 1;
	}
	return (1);
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
 * e_cust_puts - Prints a string to standard error
 * @string: string input to print
*/

void e_cust_puts(char *string)
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
 * print_numbers - Prints integers in base 10
 * @num: Number to print
 * @file_desc: The file descriptor which will receive the numbers
 * Return: Number of characters printed successfully
*/

int print_numbers(int num, int file_desc)
{
	unsigned int absolute, temp;
	int char_count = 0, iterate;
	int (*putchar_ptr)(char) = put_char;

	if (file_desc == STDERR_FILENO)
		putchar_ptr = e_put_char;

	if (num < 0)
	{
		absolute = -num;
		char_count += 1;
		putchar_ptr('-');
	}
	else
	{
		absolute = num;
	}

	temp = num;
	iterate = 1000000000;

	while (iterate > 1)
	{
		if (absolute / iterate > 0)
		{
			putchar_ptr((temp / iterate) + 48);
			char_count += 1;
		}
		temp = temp % iterate;
		iterate = iterate / 10;
	}
	putchar_ptr(temp + 48);
	char_count += 1;
	return (char_count);
}



