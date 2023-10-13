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


