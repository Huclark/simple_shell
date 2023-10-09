#include "shell.h"

/**
 * delim_checker - Inspects a character to check if it is a delimiter
 * @ch: Character to inspect
 * @delimiter: Delimiter
 * Return: 1 if true or 0 if otherwise
*/
int delim_checker(char ch, char *delimiter)
{
	int idx = 0;

	while (delimiter[idx] != '\0')
	{
		if (delimiter[idx] == ch)
			return (1);
		idx++;
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
 *Return: THe string searched
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


/**
 * pathstring_cpy - Duplicates characters in a PATH string
 * @pathstring: PATH string to duplicate
 * @idx_1: Starting position
 * @idx_2: End point
 * Return: Pointer to new buffer containing duplicated chars
*/

char *pathstring_cpy(char *pathstring, int idx_1, int idx_2)
{
	static char dup_chars[1024];
	int ite_1, ite_2;

	ite_1 = idx_1;
	ite_2 = 0;

	while (ite_1 < idx_2)
	{
		if (pathstring[ite_1] != ':')
		{
			dup_chars[ite_2] = pathstring[ite_1];
			ite_2++;
		}
		idx_1++;
	}
	dup_chars[ite_2] = 0;
	return (dup_chars);
}


