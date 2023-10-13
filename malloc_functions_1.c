#include "shell.h"

/**
 * free_str - Ensures that strings pointers are freed properly
 * @str: A pointer to a pointer to a string
*/

void free_str(char **str)
{
	char **ptr = str;

	if (str  == NULL)
		return;
	while (*str != NULL)
	{
		free(*str);
		str++;
	}
	free(ptr);
}


/**
 * shell_realloc - Replicates realloc function
 * @prev_mem_ptr: Pointer to previously allocated memory
 * @prev_size: size of previous memory
 * @curr_size: size of current memory
 * Return: pointer to old memory block
*/

void *shell_realloc(void *prev_mem_ptr, unsigned int prev_size,
						unsigned int curr_size)
{
	char *old_mem;

	if (!prev_mem_ptr)
		return (malloc(curr_size));
	if (!curr_size)
		return (free(prev_mem_ptr), NULL);
	if (curr_size == prev_size)
		return (prev_mem_ptr);

	old_mem = malloc(curr_size);
	if (!old_mem)
		return (NULL);

	if (prev_size < curr_size)
		prev_size = prev_size;
	else
		prev_size = curr_size;

	while (prev_size--)
		old_mem[prev_size] = ((char *)prev_mem_ptr)[prev_size];
	free(prev_mem_ptr);
	return (old_mem);
}



