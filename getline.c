#include "shell.h"

static ssize_t position_size;
static ssize_t bufflength;
static char container[READ_BUFFER];

/**
 * _getline - Replicates the standard getline function
 * @buffer: Line buffer
 * @n: Buffer size
 * @file_desc: File descriptor
 * Return: The number of bytes read
 *        -1 on failure.
 */
ssize_t _getline(char **buffer, size_t *n, int file_desc)
{
	size_t bytesRead = 0;
	char ch;

	if (buffer == NULL || n == NULL)
		return (-1);

	if (*buffer == NULL || *n == 0)
	{
		*n = 128;
		*buffer = (char *)malloc(*n);
		if (*buffer == NULL)
			return (-1);
	}

	while (1)
	{
		if (position_size >= bufflength)
		{
			if (fetch_input(file_desc) == -1)
				return (-1);
			if (bufflength == 0)
			{
				if (bytesRead == 0)
					return (-1);
				break;
			}
		}
		ch = container[position_size++];
		if (bytesRead >= *n - 1)
		{
			if (refill_line(buffer, n) == -1)
				return (-1);
		}
		(*buffer)[bytesRead] = ch;
		bytesRead++;
		if (ch == '\n')
			break;
	}
	(*buffer)[bytesRead] = '\0';
	return (bytesRead);
}


/**
 * fetch_input - Fetches the input from file descriptor
 * @file_desc: File descriptor
 * Return: The number of bytes read
 *        -1 on failure.
 */
ssize_t fetch_input(int file_desc)
{
	ssize_t bytesRead = read(file_desc, container, READ_BUFFER);

	if (bytesRead == -1 && errno == EINTR)
		return (fetch_input(file_desc));

	bufflength = bytesRead;
	position_size = 0;
	return (bufflength);
}

/**
 * refill_line - Memory reallocation
 * @buffer: Pointer to a pointer to the line buffer
 * @n: Pointer to the buffer size
 * Return: 0 on success
 *        -1 on failure
 */
ssize_t refill_line(char **buffer, size_t *n)
{
	size_t oldmem = *n;
	size_t newmem = (*n) * 2;
	*buffer = shell_realloc(*buffer, oldmem, newmem);

	if (buffer == NULL)
		return (-1);

	*n = newmem;
	return (0);
}

