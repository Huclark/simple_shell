#include "shell.h"

/**
* shell_exit - Handles the exit built-in command
* @argv_tkn: Null-terminated list of commands and parameters
* Return: 0 to exit shell
*/
int shell_exit(char **argv_tkn)
{
	(void)argv_tkn;
	return (0);
}


/**
* shell_cd - Handles the cd built-in command
* @argv_tkn: Null-terminated list of commands and parameters
* Return: 1 to keep shell in loop
*/
int shell_cd(char **argv_tkn)
{
	/* const char *home, *prev_dir;

	char *cwd;

	if (argv_tkn[1] == NULL || stringcompare(argv_tkn[1], "~") == 0)
	{
		home = shell_getenv("HOME");
		if (home == NULL)
			perror("HOME environment variable not set");
		else
		{
			if (chdir(home) != 0)
				perror("Error");
		}
	}
	else if (stringcompare(argv_tkn[1], "-") == 0)
	{
		prev_dir = shell_getenv("OLDPWD");
		if (prev_dir == NULL)
			perror("OLDPWD environment variable not set");
		else
			if (chdir(prev_dir) != 0)
				perror("Error");
	}
	else
	{
		if (chdir(argv_tkn[1]) != 0)
			perror("Error");
	}
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		perror("Error");
	else
	{
		if (shell_setenv("PWD", cwd, 1) != 0)
			perror("Error");
		free(cwd);
	} */
	if (argv_tkn[1] == NULL)
		perror("expected argument to cd");
	else
	{
		if (chdir(argv_tkn[1]) != 0)
			perror("error");
	}
	return (1);
}
