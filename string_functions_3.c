#include "shell.h"

/**
* string_n_cmp - Compares the first n characters of two strings
* @string1: String 1
* @string2: String 2
* @n: Bytes to compare
* Return: 0 if first n characters of both strings are the same
*         The difference between two strings if otherwise
*/
int string_n_cmp(const char *string1, const char *string2, int n)
{
	while (n > 0)
	{
		char c1 = *string1;
		char c2 = *string2;

		if (c1 == '\0' || c1 != c2)
			return ((int)(c1 - c2));

		string1++;
		string2++;
		n--;
	}
	return (0);
}


/**
 * string_n_copy - Copies a given number of bytes of
 *                a string onto another string
 * @target: Target string
 * @source: Source string
 * @bytes: Bytes to be copied
 * Return: Target string
*/

char *string_n_copy(char *target, char *source, int bytes)
{
	int idx;

	idx = 0;

	while (idx < bytes && source[idx] != '\0')
	{
		target[idx] = source[idx];
		idx++;
	}
	while (idx < bytes)
	{
		target[idx] = '\0';
		idx++;
	}

	return (target);
}


/**
 * string_n_concat - Concatenates two strings using at most
 *                   n bytes from source string
 * @target: Target string
 * @source: Source string
 * @bytes: Bytes to be used
 * Return: Target string
*/

char *string_n_concat(char *target, char *source, int bytes)
{
	int source_len = 0;
	int idx;

	for (idx = 0 ; target[idx] != '\0' ; idx++)
		source_len += 1;
	for (idx = 0 ; idx < bytes && source[idx] != '\0' ; idx++)
		target[source_len + idx] = source[idx];
	return (target);
}


/**
 **find_char - Finds a character in a string
 *@string: the string to be parsed
 *@ch: the character to look for
 *Return: The string searched
 */

char *find_char(char *string, char ch)
{
	while (*string != '\0')
	{
		if (*string == ch)
			return (string);
		string++;
	}
	return (NULL);
}

