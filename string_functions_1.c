#include "shell.h"

/**
* stringcopy - Copies a string from one string array to another
* @target: A pointer to the target string array to copy to
* @source: A pointer to the source string
* Return: A pointer to the target string
*/

char *stringcopy(char *target, char *source)
{
	int idx = 0; /* index to loop through source string */

	if (target == source || source == 0)
		return (target);

	/* Copy source string into target string */
	while (source[idx] != '\0')
	{
		target[idx] = source[idx];
		idx += 1;
	}

	target[idx] = '\0';

	return (target);
}


/**
* stringcompare - Compares two strings
* @string1: A pointer to the 1st string
* @string2: A pointer to the 2nd string
* Return: 0 if string1 = string2
*         positive or negative integer if otherwise
*/

int stringcompare(char *string1, char *string2)
{
	int idx = 0;

	while (string1[idx] != '\0' && string2[idx] != '\0')
	{
		if (string1[idx] != string2[idx])
		{
			if (string1[idx] < string2[idx] || string1[idx] > string2[idx])
				return (string1[idx] - string2[idx]);
		}
		idx += 1;
	}
	return (0);
}


/**
* stringlength - Calculates the length of a string
* @str: A pointer to the string input
* Return: Length of the string input
*/

int stringlength(char *str)
{
	int len = 0;

	while (str[len] != '\0')
		len++;

	return (len);
}


/**
* stringconcat - Concatenates two strings
* @target: A pointer to the target string array to copy to
* @source: A pointer to the source string
* Return: A pointer to the target string
*/

char *stringconcat(char *target, char *source)
{
	int targetlen = 0, idx = 0;

	while (target[idx] != '\0')
	{
		targetlen += 1;
		idx++;
	}

	idx = 0;

	while (source[idx] != '\0')
	{
		target[targetlen + idx] = source[idx];
		idx++;
	}

	target[targetlen + idx] = '\0';

	return (target);
}


/**
* stringdup - Duplicates a string from one string array to a buffer
* @source: A pointer to the source string to duplicate
* Return: A pointer to the target string
*/

char *stringdup(char *source)
{
	int len = 0, idx;
	char *target;

	if (source == NULL)
		return (NULL);

	while (source[len] != '\0')
		len++;

	target = malloc(sizeof(char) * (len + 1));

	if (target == NULL)
		return (NULL);

	for (idx = 0 ; idx <= len ; idx++)
	{
		target[idx] = source[idx];
	}

	return (target);
}
