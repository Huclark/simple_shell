#include "shell.h"

/**
 * check_for_alphabet - Checks if character is alphabet
 * @ch: Character input
 * Return: 1 if character is alphabet or 0 if otherwise
*/

int check_for_alphabet(int ch)
{
	if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
		return (1);
	else
		return (0);
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


/**
 * prefix_checker - Checks if a string starts with a prefix
 * @string: A pointer to the string to check for prefix
 * @prefix: A pointer to the prefix string to find
 * Return: (*string) If strings match prefix
 *         or NULL if there is a mismatch
*/
char *prefix_checker(const char *prefix, const char *string)
{
	int idx = 0;

	while (prefix[idx] != '\0')
	{
		if (prefix[idx] != string[idx])
			return (NULL);
		idx++;
	}

	if (prefix[idx] == '\0')
		return ((char *)string);

	return (NULL);
}


/**
 * strtok_delims - Splits a string into words using multiple delimiters
 * @string: String to tokenize
 * @delim: A string of delimiters
 * Return: An array of strings on success
 *         Or NULL if failed
*/
char **strtok_delims(char *string, char *delim)
{
	int idx1, idx2, idx3 = 0, idx4, word_count = 0;
	char **ret_str;

	if (string == NULL || string[0] == 0)
		return (NULL);
	if (delim == NULL)
		delim = " ";
	for (idx1 = 0 ; string[idx1] != '\0' ; idx1++)
		if (!delim_checker(string[idx1], delim) &&
				(delim_checker(string[idx1 + 1], delim) || !string[idx1 + 1]))
			word_count++;
	if (word_count == 0)
		return (NULL);
	ret_str = malloc((1 + word_count) * sizeof(char *));
	if (ret_str == NULL)
		return (NULL);
	idx1 = 0;
	idx2 = 0;
	while (idx2 < word_count)
	{
		while (delim_checker(string[idx1], delim))
			idx1++;
		while (!delim_checker(string[idx1 + idx3], delim) && string[idx1 + idx3])
			idx3++;
		ret_str[idx2] = malloc((idx3 + 1) * sizeof(char));
		if (ret_str[idx2] == NULL)
		{
			for (idx3 = 0 ; idx3 < idx2 ; idx3++)
				free(ret_str[idx3]);
			free(ret_str);
			return (NULL);
		}
		for (idx4 = 0; idx4 < idx3; idx4++)
			ret_str[idx2][idx4] = string[idx1++];
		ret_str[idx2][idx4] = 0;
		idx2++;
	}
	ret_str[idx2] = NULL;
	return (ret_str);
}


/**
 * strtok_delim - Splits a string into words using just a single delimiter.
 * @string: String to tokenize
 * @delim: Delimiter character
 * Return: An array of strings on success
 *         Or NULL if failed
*/
char **strtok_delim(char *string, char delim)
{
	int idx1, idx2, idx3, idx4, word_count = 0;
	char **ret_str;

	if (string == NULL || string[0] == 0)
		return (NULL);
	for (idx1 = 0; string[idx1] != '\0'; idx1++)
		if ((string[idx1] != delim && string[idx1 + 1] == delim) ||
				    (string[idx1] != delim && !string[idx1 + 1]) ||
							string[idx1 + 1] == delim)
			word_count++;
	if (word_count == 0)
		return (NULL);
	ret_str = malloc((1 + word_count) * sizeof(char *));
	if (!ret_str)
		return (NULL);
	for (idx1 = 0, idx2 = 0; idx2 < word_count; idx2++)
	{
		while (string[idx1] == delim && string[idx1] != delim)
			idx1++;
		idx3 = 0;
		while (string[idx1 + idx3] != delim &&
				string[idx1 + idx3] && string[idx1 + idx3] != delim)
			idx3++;
		ret_str[idx2] = malloc((idx3 + 1) * sizeof(char));
		if (!ret_str[idx2])
		{
			for (idx3 = 0; idx3 < idx2; idx3++)
				free(ret_str[idx3]);
			free(ret_str);
			return (NULL);
		}
		for (idx4 = 0; idx4 < idx3; idx4++)
			ret_str[idx2][idx4] = string[idx1++];
		ret_str[idx2][idx4] = 0;
	}
	ret_str[idx2] = NULL;
	return (ret_str);
}


