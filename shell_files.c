#include "shell.h"

/**
 * save_history - Saves command history to a file by appending
 *                to an existing file or creating a new file
 * @my_data: A pointer to the data_hub struct
 * Return: 1 on sucess or -1 if otherwise
*/

int save_history(data_hub *my_data)
{
	ssize_t file_desc;
	char *file_name_ = history_pathname(my_data);
	shell_lst *node_ptr = NULL;

	if (file_name_ == NULL)
		return (-1);

	file_desc = open(file_name_, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_name_);
	if (file_desc == -1)
		return (-1);

	node_ptr = my_data->shell_history;

	while (node_ptr != NULL)
	{
		puts_file_desc(node_ptr->string, file_desc);
		put_file_desc('\n', file_desc);
		node_ptr = node_ptr->link_node;
	}

	put_file_desc(EMPTY_BUFFER, file_desc);
	close(file_desc);
	return (1);
}


/**
 * history_pathname - Constructs the path to the history file
 * @my_data: A pointer to the data_hub struct
 * Return: A buffer containing the complete path to history file
*/

char *history_pathname(data_hub *my_data)
{
	char *hist_buff;
	char *home_directory = get_matching_env_variable("HOME=", my_data);

	if (home_directory == NULL)
		return (NULL);

	hist_buff = malloc(sizeof(char) * (stringlength(home_directory)
						+ stringlength(HISTORY_FILENAME) + 2));
	if (hist_buff == NULL)
		return (NULL);

	hist_buff[0] = 0;

	stringcopy(hist_buff, home_directory);
	stringconcat(hist_buff, "/");
	stringconcat(hist_buff, HISTORY_FILENAME);

	return (hist_buff);
}


/**
 * shell_history_list - Adds a new node to the shell history list
 * @my_data: A pointer to data_hub struct
 * @history_buffer: Buffer for history string
 * @hist_line_counter: History line-count.
 * Return: 0 on success
*/

int shell_history_list(data_hub *my_data, char *history_buffer,
							int hist_line_counter)
{
	shell_lst *new_node = NULL;

	if (my_data->shell_history != NULL)
		new_node = my_data->shell_history;

	add_shell_list_end(&new_node, history_buffer, hist_line_counter);

	if (my_data->shell_history == NULL)
		my_data->shell_history = new_node;

	return (0);
}



