#include "shell.h"

/**
 * shell_loop - Displays a type prompt.
 *              Reads and executes command and parameters from command line.
 *              Displays type prompt again each time a
 *               command has been executed.
 * @argv: Argument vector
*/
void shell_loop(char **argv)
{
	char **arg_parse, *cli_arg;
	int loop_status, line_count = 1;

	if (isatty(STDIN_FILENO))
	{
		do {
		cust_puts("-->> ");
		fflush(stdout);
		cli_arg = shell_getline();
		arg_parse = parse_line(cli_arg);
		loop_status = shell_exec(arg_parse, argv, line_count);

		free(cli_arg);
		free(arg_parse);
		line_count++;
	}	while (loop_status);
	}
	else
	{
		cli_arg = shell_getline();
		arg_parse = parse_line(cli_arg);
		shell_exec(arg_parse, argv, line_count);

		free(cli_arg);
		free(arg_parse);
	}
}


/**
 * shell_getline - Reads a line from standard input for parsing
 * Return: The command and parameters from standard input
*/
char *shell_getline(void)
{
	unsigned int buflength = READ_BUFFER, position_size = 0;
	char *line_buffer = malloc(sizeof(char) * buflength);
	int ch;

	if (line_buffer == NULL) /* If malloc fails */
	{
		perror("Failed to allocate memory");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		/* Read a character */
		ch = sh_getchar();

		if (ch == EOF)
			exit(EXIT_SUCCESS);

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
 * parse_line - Separates the command string into
 *              commands and parameters
 * @cli_arg: Command string from stdin
 * Return: A null-terminated array of token strings.
*/
char **parse_line(char *cli_arg)
{
	char **tkn_buf, **tkn_cpy, *tkn_str;
	unsigned int buflength = TOKEN_BUFFER, ptn_size = 0;

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
 * @argv_tkn: Null-terminated list of commands and parameters
 * @argv: Argument vector
 * @line_count: The number of lines processed
 * Return: 1 if to continue shell loop
 *         0 to exit shell
*/
int shell_exec(char **argv_tkn, char **argv, int line_count)
{
	int idx = 0, builtins_count;

	char *builtins[] = {
		"exit",
		"cd",
	};

	int (*bltin_function[])(char **) = {
		&shell_exit,
		&shell_cd,
	};

	/* User entered an empty comand (empty string or white space) */
	if (argv_tkn[0] == NULL)
		return (1);

	builtins_count = sizeof(builtins) / sizeof(char *);

	while (idx < builtins_count)
	{
		if (stringcompare(argv_tkn[0], builtins[idx]) == 0)
			return ((*bltin_function[idx])(argv_tkn));
		idx++;
	}
	return (fork_cmd(argv_tkn, argv, line_count));
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
		if (isatty(STDIN_FILENO))
		{
			cust_puts(argv[0]);
			cust_puts(": No such file or directory\n");
		}
		else
			error_output(argv[0], argv_tkn, "not found", line_count);
		return (1);
	}

	child_process = fork();

	if (child_process == -1)
		perror("Fork failed");
	if (child_process == 0)
	{
		if (execve(fullpath, argv_tkn, shell_env()) == -1)
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
