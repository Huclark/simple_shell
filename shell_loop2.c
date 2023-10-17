#include "shell.h"

/**
 * parse_line2 - Separates the command string into
 *              commands and parameters
 * @cli_arg: Command string from stdin
 * Return: A null-terminated array of token strings.
*/
char **parse_line2(char *cli_arg)
{
	char **tkn_buf, **tkn_cpy, *tkn_str;
	unsigned int buflength = TOKEN_BUFFER, ptn_size = 0;

	if (find_char(cli_arg, ';') == NULL)
		return (NULL);

	tkn_buf = malloc(sizeof(char *) * buflength);

	if (tkn_buf == NULL)
	{
		perror("Failed to allocate memory");
		exit(EXIT_FAILURE);
	}
	tkn_str = strtok_delims(cli_arg, ";");

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
		tkn_str = strtok_delims(NULL, ";");
	}
	tkn_buf[ptn_size] = NULL;

	return (tkn_buf);
}


/**
 * interactive -  Starts the shell in interactive mode
 * @argv: Argument vector
 * Return: 0 on success, -1 on failure
*/
int interactive(char **argv)
{
	char **arg_parse1, **arg_parse2, *cli_arg1, *cli_arg2, *cli_arg3;
	int loop_status, line_count = 1;

	do {
		cust_puts("-->> ");
		fflush(stdout);

		cli_arg1 = shell_getline();
		cli_arg2 = stringdup(cli_arg1);
		cli_arg3 = stringdup(cli_arg1);

		arg_parse1 = parse_line1(cli_arg1);
		arg_parse2 = parse_line2(cli_arg2);

		if (stringcompare(arg_parse1[0], "exit") == 0)
			loop_status = shell_exit(argv, arg_parse1, line_count);

		else
			loop_status = shell_exec(arg_parse1, arg_parse2, argv,
										cli_arg3, line_count);

		free_loop(cli_arg1, cli_arg2, cli_arg3, arg_parse1, arg_parse2);

		line_count++;
		} while (loop_status == 1);

		return (loop_status);
}


/**
 * non_interactive -  Starts the shell in non-interactive mode
 * @argv: Argument vector
 * Return: 0 on success
*/
int non_interactive(char **argv)
{
	char **arg_parse1, **arg_parse2, *cli_arg1, *cli_arg2, *cli_arg3;
	int loop_status, line_count = 1;

	cli_arg1 = shell_getline();
	cli_arg2 = strdup(cli_arg1);
	cli_arg3 = stringdup(cli_arg1);
	arg_parse1 = parse_line1(cli_arg1);
	arg_parse2 = parse_line2(cli_arg2);
	if (stringcompare(arg_parse1[0], "exit") == 0)
	{
		loop_status = shell_exit(argv, arg_parse1, line_count);
		free_loop(cli_arg1, cli_arg2, cli_arg3, arg_parse1, arg_parse2);
		return (loop_status);
	}
	else
	{
		shell_exec(arg_parse1, arg_parse2, argv, cli_arg3, line_count);
		free_loop(cli_arg1, cli_arg2, cli_arg3, arg_parse1, arg_parse2);
		return (EXIT_SUCCESS);
	}
}
