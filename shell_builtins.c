#include "shell.h"

/**
* shell_exit - Handles the exit built-in command
* @argv: Argument vector
* @argv_tkn: Null-terminated list of commands and parameters
* @line_count: Line count
* Return: 0 if there is no argument to "exit"
*         1 if argument is invalid in interactive mode
*         2 if argument is invalid in non-interactive mode
*         Exit status if a valid argument is passed to "exit"
*/
int shell_exit(char **argv, char **argv_tkn, int line_count)
{
	char *num_string;

	if (argv_tkn[1] != NULL)
	{
		num_string = argv_tkn[1];

		while (*num_string != '\0')
		{
			if (is_digit(*num_string) == 0)
			{
				exit_error_output(argv[0], argv_tkn, "Illegal number", line_count);
				if (isatty(STDIN_FILENO))
					return (1);
				else
					return (2);
			}
			num_string++;
		}
		return (atoi_(argv_tkn[1]));
	}
	else
		return (0);
}


/**
* shell_cd - Handles the cd built-in command
* @argv: Argument vector
* @argv_tkn: Null-terminated list of commands and parameters
* @line_count: Line count
* @head: A pointer to the head of env_list
* Return: 1 to keep shell in loop
*/
int shell_cd(char **argv, char **argv_tkn, int line_count, env_list **head)
{
	char *home, *prev_dir;
	char *cwd_p = malloc(PATH_MAX), *cwd_c = malloc(PATH_MAX);

	if (cwd_p == NULL || cwd_c == NULL)
		return (1);

	getcwd(cwd_p, PATH_MAX);

	if (argv_tkn[1] == NULL || stringcompare(argv_tkn[1], "~") == 0)
	{
		home = shell_getenv(head, "HOME");
		chdir(home);
		shell_setenv(head, "OLDPWD", cwd_p, 1);
	}

	else if (stringcompare(argv_tkn[1], "-") == 0)
	{
		prev_dir = shell_getenv(head, "OLDPWD");
		chdir(prev_dir);
		shell_setenv(head, "OLDPWD", cwd_p, 1);
	}

	else
	{
		if (chdir(argv_tkn[1]) != 0)
			cd_error_output(argv[0], argv_tkn, "can't cd to", line_count);
		else
			shell_setenv(head, "OLDPWD", cwd_p, 1);
	}

	getcwd(cwd_c, PATH_MAX);
	shell_setenv(head, "PWD", cwd_c, 1);

	free(cwd_p);
	free(cwd_c);

	return (1);
}


/**
 * env_builtin - Handles the "env" built-in command
 * @argv: Argument vector
 * @argv_tkn: Null-terminated list of commands and parameters
 * @line_count: Line count
 * @head: Pointer to the head of env_list
 * Return: Always 1
*/
int env_builtin(char **argv, char **argv_tkn, int line_count, env_list **head)
{
	env_list *node_ptr = *head;

	(void)argv_tkn;
	(void)argv;
	(void)line_count;

	while (node_ptr != NULL)
	{
		cust_puts(node_ptr->var_name);
		put_char('=');
		cust_puts(node_ptr->var_value);
		put_char('\n');
		node_ptr = node_ptr->next;
	}
	return (1);
}




