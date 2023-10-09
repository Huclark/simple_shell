#include "shell.h"

/**
 * shell_list_strings - Lists all strings of the shell_lst linked list
 *                      (shell_lst->string)
 * @head: Head pointer
 * Return: An array of strings
*/

char **shell_list_strings(shell_lst *head)
{
	shell_lst *traverse = head;
	size_t idx_1, idx_2;
	char **string1, *string2;

	idx_1 = shell_list_len(head);

	if (head == NULL || !idx_1)
		return (NULL);
	string1 = malloc(sizeof(char *) * (idx_1 + 1));
	if (string1 == NULL)
		return (NULL);

	idx_1 = 0;

	while (traverse != NULL)
	{
		string2 = malloc(stringlength(traverse->string) + 1);

		if (string2 == NULL)
		{
			idx_2 = 0;

			while (idx_2 < idx_1)
			{
				free(string1[idx_2]);
				idx_2++;
			}
			free(string1);
			return (NULL);
		}

		string2 = stringcopy(string2, traverse->string);
		string1[idx_1] = string2;
		traverse = traverse->link_node;
	}
	string1[idx_1] = NULL;
	return (string1);
}


/**
 * add_shell_list_end - Adds a new node to the end of shell_lst
 * @head: Head pointer
 * @string: The string element of shell_lst
 * @n: Index
 * Return: s
*/

shell_lst *add_shell_list_end(shell_lst **head, const char *string, int n)
{
	shell_lst *node_1, *node_2;

	if (head == NULL)
		return (NULL);
	node_2 = *head;
	node_1 = malloc(sizeof(shell_lst));

	if (node_1 == NULL)
		return (NULL);

	memory_fill((void *)node_1, '\0', sizeof(shell_lst));
	node_1->n = n;

	if (string != NULL)
	{
		node_1->string = stringdup(string);

		if (node_1->string == NULL)
		{
			free(node_1);
			return (NULL);
		}
	}
	if (node_2 != NULL)
	{
		while (node_2->link_node != NULL)
			node_2 = node_2->link_node;

		node_2->link_node = node_1;
		node_1->link_node = NULL;
	}
	else
	{
		*head = node_1;
		node_1->link_node = NULL;
	}
	return (node_2);
}


/**
 * shell_list_len - Checks the length of shell_lst linked list
 * @head_ptr: Pointer to the beginning of the linked list
 * Return: Length of the linked list
*/

size_t shell_list_len(const shell_lst *head_ptr)
{
	size_t idx = 0;

	while (head_ptr != NULL)
	{
		idx += 1;
		head_ptr = head_ptr->link_node;
	}
	return (idx);
}
