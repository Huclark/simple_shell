#include "shell.h"

/**
* fork_child - forks a child to execute command
* @my_data: pointer to data_hub struct
*/

void fork_child(data_hub *my_data)
{
	pid_t child_process = fork();

	if (child_process == -1)
	{
		perror("Unsuccessful:");
		return;
	}
	if (child_process == 0)
	{
		if (execve(my_data->path_name, my_data->argv,
		retrieve_env_var(my_data)) == -1)
		{
			empty_data_hub(1, my_data);
			if (errno == EACCES)
				exit(2);
			exit(1);
		}
	}
	else
	{
		wait(&(my_data->return_stats));
		if (WIFEXITED(my_data->return_stats))
		{
			my_data->return_stats = WEXITSTATUS(my_data->return_stats);
			if (my_data->return_stats == 2)
			{
				error_output(my_data, "Access denied");
				e_cust_puts("\n");
			}
		}
	}
}



/**
 * command_search - Searches through the PATH to locate a command
 * @my_data: Struct variable for data_hub
*/

void command_search(data_hub *my_data)
{
	char *path_pointer = NULL;
	int idx = 0, non_delim_count = 0;

	my_data->path_name = my_data->argv[0];

	if (my_data->line_flagger == 1)
	{
		my_data->line_flagger -= 1;
		my_data->line_counter_ += 1;
	}

	while (my_data->arguments_delim[idx] != '\0')
	{
		if (!delim_checker(my_data->arguments_delim[idx], " \t\n"))
			non_delim_count += 1;
		idx += 1;
	}
	if (non_delim_count == 0)
		return;

	path_pointer = cmd_in_path(my_data,
									get_matching_env_variable("PATH=", my_data), my_data->argv[0]);

	if (path_pointer != NULL)
	{
		my_data->path_name = path_pointer;
		fork_child(my_data);
	}
	else
	{
		if ((interactive_mode(my_data) ||
				get_matching_env_variable("PATH=", my_data) ||
				my_data->argv[0][0] == '/') && cmd_checker(my_data->argv[0], my_data))
		{
			fork_child(my_data);
		}
		else if (*(my_data->arguments_delim) != '\n')
			error_output(my_data, "not found\n");
	}
}


/**
 * interactive_mode - Checks if shell is interactive or not
 * @my_data: A pointer to the datahub struct address
 * Return: 1 if interactive
 *         0 if otherwise
*/

int interactive_mode(data_hub *my_data)
{
	int ret_value;

	if (isatty(STDIN_FILENO) && my_data->check_file_desc <= 2)
		ret_value = 1;

	else
		ret_value = 0;

	return (ret_value);
}


/**
 * builtin_command - Handles built-in commands
 * @my_data: A pointer to the data_hub struct
 * Return: 0 if the built-in command successfully executed
 *        -1 if the built-in command was not found
 *         1 if the built-in command did not successfully executed
 *         2 if the built-in command exit()
*/

int builtin_command(data_hub *my_data)
{
	int ret_value = -1, idx = 0;

	builtin builtin_init[] = {
		{"cd", shell_cd},
		{NULL, NULL}
	};

	while (builtin_init[idx].builtin_cmd)
	{
		if (stringcompare(builtin_init[idx].builtin_cmd, my_data->argv[0]))
		{
			my_data->line_counter_ += 1;
			ret_value = builtin_init[idx].builtin_func(my_data);
			break;
		}
		idx++;
	}

	return (ret_value);
}


/**
 * shell_loop - Displays a type prompt.
 *              Reads and executes command and parameters from command line.
 *              Displays type prompt again each time a
 *               command has been executed.
 * @my_data: A pointer to the data_hub struct.
 * @argv: Argument vector
 * Return: 0 on success
*/

int shell_loop(data_hub *my_data, char **argv)
{
	int ret_value = 0;
	ssize_t func_return = 0;

	while (func_return != -1 && ret_value != -2)
	{
		my_data->argv = NULL;
		my_data->cli_argv = NULL;
		my_data->argc = 0;
		my_data->path_name = NULL;

		if (interactive_mode(my_data))
			cust_puts(":) ");
		e_put_char(EMPTY_BUFFER);
		func_return = read_cmd_line(my_data);
		if (func_return != -1)
		{
			dh_init(my_data, argv);
			ret_value = builtin_command(my_data);
			if (ret_value == -1)
				command_search(my_data);
		}
		else if (interactive_mode(my_data))
			put_char('\n');
		empty_data_hub(0, my_data);
	}
	save_history(my_data);
	empty_data_hub(1, my_data);
	if (!interactive_mode(my_data) && my_data->return_stats)
		exit(my_data->return_stats);
	if (ret_value == -2)
	{
		if (my_data->exiterr_no == -1)
			exit(my_data->return_stats);
		exit(my_data->exiterr_no);
	}
	return (ret_value);
}

