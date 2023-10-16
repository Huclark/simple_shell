#include "shell.h"

/**
 * print_numbers - function prints a decimal (integer) number (base 10)
 * @num_to_print: the num_to_print
 * Return: number of characters printed
 */
int print_numbers(int num_to_print)
{
	int idx, __counter = 0;
	unsigned int absolute, curr_num;

	if (num_to_print < 0)
	{
		absolute = -num_to_print;
		put_char('-');
		__counter++;
	}
	else
		absolute = num_to_print;
	curr_num = absolute;
	for (idx = 1000000000; idx > 1; idx /= 10)
	{
		if (absolute / idx)
		{
			put_char('0' + curr_num / idx);
			__counter++;
		}
		curr_num %= idx;
	}
	put_char('0' + curr_num);
	__counter++;

	return (__counter);
}
