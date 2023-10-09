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
* empty_data_hub - Frees the data_hub struct
* @my_data: data_hub struct variable
* @true: Flag to free entire struct
*/

void empty_data_hub(int true, data_hub *my_data)
{
	my_data->path_name = NULL;
	free_str(my_data->argv);
	my_data->argv = NULL;

	if (true != 0)
	{
		if (my_data->shell_env)
			free_shell_list(&(my_data->shell_env));

		if (my_data->check_file_desc > 2)
			close(my_data->check_file_desc);

		if (my_data->shell_history)
			free_shell_list(&(my_data->shell_history));

		free_str(my_data->child_env);
			my_data->child_env = NULL;

		put_char(EMPTY_BUFFER);
	}
}


/**
* free_shell_list - Frees the shell_list linked list
* @ptr_to_head: A pointer to head of list
*/

void free_shell_list(shell_lst **ptr_to_head)
{
	shell_lst *head, *current_node, *temp;

	if (*ptr_to_head == NULL || ptr_to_head == NULL)
		return;

	head = *ptr_to_head;
	current_node = head;

	while (current_node != NULL)
	{
		temp = current_node->link_node;
		free(current_node->string);
		free(current_node);
		current_node = temp;
	}
	*ptr_to_head = NULL;
}


/**
 * memory_fill - Fills the memory
 * @mem_address: A pointer to the memory address to fill
 * @content: The content to fill the memory address with
 * @bytes: Size of bytes to be used
 * Return: A pointer to the memory address
*/

char *memory_fill(char *mem_address, char content, unsigned int bytes)
{
	unsigned int idx = 0;

	while (idx < bytes)
	{
		mem_address[idx] = content;
		idx++;
	}

	return (mem_address);
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



