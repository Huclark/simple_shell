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
* Return: 1 to keep shell in loop
*/
int shell_cd(char **argv, char **argv_tkn, int line_count)
{
	char *dir, *prev_dir = getenv("OLDPWD"), *home = getenv("HOME");
	char cwd_c[READ_BUFFER];

	if (prev_dir == NULL || home == NULL)
	{
		perror("getenv: Failed to fetch environment value");
		return (1);
	}

	if (argv_tkn[1] == NULL || stringcompare(argv_tkn[1], "~") == 0)
		dir = home;

	else if (stringcompare(argv_tkn[1], "-") == 0)
	{
		dir = prev_dir;
		cust_puts(dir);
		put_char('\n');
	}

	else
		dir = argv_tkn[1];

	if (chdir(dir) != 0)
	{
		cd_error_output(argv[0], argv_tkn, "can't cd to", line_count);
		return (1);
	}

	setenv("OLDPWD", getenv("PWD"), 1);

	if (getcwd(cwd_c, sizeof(cwd_c)) != NULL)
		setenv("PWD", cwd_c, 1);
	else
		perror("getcwd: Could not fetch current working directory");

	return (1);
}


/**
 * env_builtin - Handles the "env" built-in command
 * @argv: Argument vector
 * @argv_tkn: Null-terminated list of commands and parameters
 * @line_count: Line count
 * Return: Always 1
*/
int env_builtin(char **argv, char **argv_tkn, int line_count)
{
	char **env_ptr = environ;

	(void)argv_tkn;
	(void)argv;
	(void)line_count;

	while (*env_ptr)
	{
		cust_puts(*env_ptr);
		put_char('\n');
		env_ptr++;
	}

	return (1);
}


/**
 * set_env_builtin - setenv built-in command which adds or modifies
 *                   an environment variable
 * @argv: Argument vector
 * @argv_tkn: Null-terminated list of commands and parameters
 * @line_count: Line count
 * Return: Always 1
*/
int set_env_builtin(char **argv, char **argv_tkn, int line_count)
{
	if (argv_tkn[1] == NULL || argv_tkn[2] == NULL)
	{
		error_output(argv[0], argv_tkn, "Usage: setenv VARIABLE VALUE", line_count);
		return (1);
	}

	if (setenv(argv_tkn[1], argv_tkn[2], 1) != 0)
	{
		perror("Failed to set environment variable");
		return (1);
	}
	return (1);
}


/**
 * unset_env_builtin - unsetenv built-in command which removes
 *                     an environment variable
 * @argv: Argument vector
 * @argv_tkn: Null-terminated list of commands and parameters
 * @line_count: Line count
 * Return: Always 1
*/
int unset_env_builtin(char **argv, char **argv_tkn, int line_count)
{
	if (argv_tkn[1] == NULL)
	{
		error_output(argv[0], argv_tkn, "Usage: setenv VARIABLE VALUE", line_count);
		return (1);
	}

	if (unsetenv(argv_tkn[1]) != 0)
	{
		perror("Failed to set environment variable");
		return (1);
	}
	return (1);
}
