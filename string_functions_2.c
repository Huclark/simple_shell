#include "shell.h"

/**
 * strtok_delims - Splits a string into words using multiple delimiters
 * @string: String to tokenize
 * @delim: A string of delimiters
 * Return: An array of strings on success
 *         Or NULL if failed
*/
char *strtok_delims(char *string, char *delim)
{
	static char *nextToken;

	char *token;

	if (string != NULL)
		nextToken = string;

	if (nextToken == NULL)
		return (NULL);

	while (*nextToken != '\0' && delim_checker(delim, *nextToken))
		nextToken++;

	if (*nextToken == '\0')
		return (NULL);

	token = nextToken;
	while (*nextToken != '\0' && !delim_checker(delim, *nextToken))
		nextToken++;

	if (*nextToken != '\0')
		*nextToken++ = '\0';

	return (token);
}


/**
 * delim_checker - Inspects a character to check if it is a delimiter
 * @string: String to inspect
 * @delimiter: Delimiter
 * Return: 1 if character matches delim
 *         0 if there is no match found
*/
char *delim_checker(char *string, int delimiter)
{
	while (*string != '\0')
	{
		if (*string == delimiter)
			return (string);
		string++;
	}
	return (NULL);
}


/**
 * sh_getchar - Reads a character from stdin
 * Return: The character read (tyypecast as an int)
*/
int sh_getchar(void)
{
	char ch;

	if (read(0, &ch, 1) == 1)
		return ((int)ch);
	else
		return (EOF);
}


/**
 * itostr - Converts an integer to a string.
 * @num: The integer to be converted.
 *
 * Return: A dynamically allocated string containing the integer.
 */
char *itostr(int num)
{
	char *str;
	int idx, temp = num;
	int no_of_digs = (num == 0) ? 1 : 0;

	while (temp != 0)
	{
		no_of_digs++;
		temp /= 10;
	}

	str = (char *)malloc(no_of_digs + 1);

	if (str == NULL)
		return (NULL);

	idx = no_of_digs - 1;

	while (idx >= 0)
	{
		str[idx] = '0' + (num % 10);
		num /= 10;
		idx--;
	}

	str[no_of_digs] = '\0';

	return (str);
}


/**
 * atoi_ - Converts a string to an integer
 * @string: String to convert to integeger
 * Return: The number converted from the string
 *         0 if no number is found
*/
int atoi_(char *string)
{
	int idx = 0, d = 0, n = 0, length = 0, f = 0, digit = 0;

	while (string[length] != '\0')
		length++;

	while (idx < length && f == 0)
	{
		if (string[idx] == '-')
			++d;

		if (string[idx] >= '0' && string[idx] <= '9')
		{
			digit = string[idx] - '0';
			if (d % 2)
				digit = -digit;
			n = n * 10 + digit;
			f = 1;
			if (string[idx + 1] < '0' || string[idx + 1] > '9')
				break;
			f = 0;
		}
		idx++;
	}

	if (f == 0)
		return (0);

	return (n);
}

