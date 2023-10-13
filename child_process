#include "shell.h"

/**
 * child_process - Creates the child process and executes the command
 * @argv_tkn: Null-terminated list of commands and parameters
 * @argv: Argument vector
 * @fullpath: Full path name to command
 * @line_count: The number of lines processed
 * Return: 1 on success
*/
int child_process(char **argv_tkn, char **argv,
					char *fullpath, int line_count)
{
	int ret_status;
	pid_t child_process = fork();

	if (child_process == -1)
		perror("Fork failed");
	if (child_process == 0)
	{
		if (find_char(argv_tkn[0], '/') == NULL)
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
			if (execve(argv_tkn[0], argv_tkn, shell_env()) == -1)
			{
				if (errno == EACCES)
					perror("Permission denied for execve");
				else
					error_output(argv[0], argv_tkn, "not found", line_count);
				exit(EXIT_FAILURE);
			}
		}
	}
	else
	{
		do {
			waitpid(child_process, &ret_status, WUNTRACED);
		} while (!WIFEXITED(ret_status) && !WIFSIGNALED(ret_status));
	}
	if (fullpath != NULL)
		free(fullpath);
	return (1);
}
