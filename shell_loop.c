#include "shell.h"

/**
 * shell_loop - Displays a type prompt.
 *              Reads and executes command and parameters from command line.
 *              Displays type prompt again each time a
 *               command has been executed.
 * @argv: Argument vector
 * Return: Loop status
*/
int shell_loop(char **argv)
{
	if (isatty(STDIN_FILENO))
	{
		return (interactive(argv));
	}
	else
	{
		return (non_interactive(argv));
	}
}


/**
 * shell_getline - Reads a line from standard input for parsing
 * Return: The command and parameters from standard input
*/
char *shell_getline(void)
{
	unsigned int buflength = READ_BUFFER, position_size = 0;
	int ch;
	char *line_buffer = malloc(sizeof(char) * buflength);

	if (line_buffer == NULL) /* If malloc fails */
	{
		perror("Failed to allocate memory");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		ch = sh_getchar();
		if (ch == EOF)
			exit(EXIT_SUCCESS);
		if (ch == '\n' && position_size == 0)
		{
			free(line_buffer);
			return (NULL);
		}
		else if (ch == '\n')
		{
			line_buffer[position_size] = '\0';
			return (line_buffer);
		}
		else
			line_buffer[position_size] = ch;
		position_size += 1;
	}
	/* Realloc if we have exceeded size threshold */
	if (position_size >= buflength)
	{
		buflength += READ_BUFFER;
		line_buffer = shell_realloc(line_buffer, buflength,
									sizeof(char) * buflength);
		if (line_buffer == NULL)
		{
			perror("Failed to allocate memory");
			exit(EXIT_FAILURE);
		}
	}
}


/**
 * parse_line1 - Separates the command string into
 *              commands and parameters
 * @cli_arg: Command string from stdin
 * Return: A null-terminated array of token strings.
*/
char **parse_line1(char *cli_arg)
{
	char **tkn_buf, **tkn_cpy, *tkn_str;
	unsigned int buflength = TOKEN_BUFFER, ptn_size = 0;

	if (cli_arg == NULL)
		return (NULL);

	tkn_buf = malloc(sizeof(char *) * buflength);

	if (tkn_buf == NULL)
	{
		perror("Failed to allocate memory");
		exit(EXIT_FAILURE);
	}

	tkn_str = strtok_delims(cli_arg, DELIMITERS);

	while (tkn_str != NULL)
	{
		tkn_buf[ptn_size] = tkn_str;
		ptn_size++;

		if (ptn_size >= buflength)
		{
			buflength += TOKEN_BUFFER;
			tkn_cpy = tkn_buf;
			tkn_buf = shell_realloc(tkn_buf, buflength, sizeof(char *) * buflength);

			if (!tkn_buf)
			{
				free(tkn_cpy);
				perror("Failed to re-allocate memory");
				exit(EXIT_FAILURE);
			}
		}
		tkn_str = strtok_delims(NULL, DELIMITERS);
	}
	tkn_buf[ptn_size] = NULL;
	return (tkn_buf);
}


/**
 * shell_exec - Executes the parsed command
 * @argv_tkn1: Null-terminated array without ':'
 * @argv_tkn2: NUll_terminated array which handles ':'
 * @argv: Argument vector
 * @cli_arg: String input from getline
 * @line_count: The number of lines processed
 * Return: Always 1
*/
int shell_exec(char **argv_tkn1, char **argv_tkn2, char **argv,
				char *cli_arg, int line_count)
{
	int idx = 0, builtins_count, status;

	char *builtins[] = {
		"cd",
		"env",
		"setenv",
		"unsetenv",
	};
	int (*bltin_function[])(char **, char **, int) = {
		&shell_cd,
		&env_builtin,
		&set_env_builtin,
		&unset_env_builtin,
	};
	/* User entered an empty comand (empty string or white space) */
	if (cli_arg == NULL)
		return (1);

	builtins_count = sizeof(builtins) / sizeof(char *);

	while (idx < builtins_count)
	{
		if (stringcompare(argv_tkn1[0], builtins[idx]) == 0)
		{
			status = (*bltin_function[idx])(argv, argv_tkn1, line_count);
			return (status);
		}
		idx++;
	}
	if (find_char(cli_arg, ';') != NULL)
	{
		while (*argv_tkn2)
		{
			fork_cmd(parse_line1(*argv_tkn2), argv, line_count);
			argv_tkn2++;
		}
	}
	else
		fork_cmd(argv_tkn1, argv, line_count);
	return (1);
}


/**
 * fork_cmd - Forks a child process and waits for it to execute
 *            a command and terminate
 * @argv_tkn: Null-terminated list of commands and parameters
 * @argv: Argument vector
 * @line_count: The number of lines processed
 * Return: 1 on success, 0 if otherwise
*/
int fork_cmd(char **argv_tkn, char **argv, int line_count)
{
	int ret_status;
	char *fullpath = find_command(argv_tkn);
	pid_t child_process;

	if (fullpath == NULL)
	{
		error_output(argv[0], argv_tkn, "not found", line_count);
		return (1);
	}

	child_process = fork();

	if (child_process == -1)
		perror("Fork failed");
	if (child_process == 0)
	{
		if (execve(fullpath, argv_tkn, environ) == -1)
		{
			if (errno == EACCES)
				perror("Permission denied for execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		do {
			waitpid(child_process, &ret_status, WUNTRACED);
		} while (!WIFEXITED(ret_status) && !WIFSIGNALED(ret_status));
	}
	free(fullpath);
	return (1);
}
