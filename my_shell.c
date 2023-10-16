#include "shell.h"

/**
* main - main function for shell program
* @argc: Argument count
* @argv: Argument vector
* Return: The exit code (loop_status)
*/

int main(int argc, char **argv)
{
	env_list *head = env_list_init(environ);
	env_list *temp;
	int loop_status;

	(void)argc;

	loop_status = shell_loop(argv, &head);

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp);
	}

	return (loop_status);
}
