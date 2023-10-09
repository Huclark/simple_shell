#include "shell.h"

/**
 * read_cmd_line - Reads command line (Excludes newline)
 * @my_data: A pointer to data_hub struct
 * Return: Number of bytes read.
*/
ssize_t read_cmd_line(data_hub *my_data)
{
	ssize_t func_return = 0;
	static size_t idx1, idx2, cmd_length;
	static char *cmd_buff_;
	char **buffer_ptr = &(my_data->cli_argv), *ptr;

	put_char(EMPTY_BUFFER);
	func_return = chained_cmd_buff(my_data, &cmd_buff_, &cmd_length);
	if (func_return == -1)
		return (-1);
	if (cmd_length != 0)
	{
		idx2 = idx1;
		ptr = cmd_buff_ + idx1;

		upd_chain(my_data, cmd_buff_, &idx2, idx1, cmd_length);

		while (idx2 < cmd_length)
		{
			if (chain_test(my_data, cmd_buff_, &idx2))
				break;
			idx2 += 1;
		}

		idx1 = idx2 + 1;

		if (idx1 >= cmd_length)
		{
			idx1 = cmd_length = 0;
			my_data->cmd_mode = DEFAULT_CMD;
		}
		*buffer_ptr = ptr;
		return (stringlength(ptr));
	}
	*buffer_ptr = cmd_buff_;
	return (func_return);
}


/**
 * dh_init - Initialization of data_hub struct
 * @my_data: A pointer to the data_hub struct
 * @argv: Argument vector
*/
void dh_init(data_hub *my_data, char **argv)
{
	int idx = 0;

	my_data->file_name_ = argv[0];
	if (my_data->cli_argv != NULL)
	{
		my_data->argv = strtok_delims(my_data->cli_argv, " \t");
		if (my_data->argv == NULL)
		{
			my_data->argv = malloc(sizeof(char *) * 2);
			if (my_data->argv != NULL)
			{
				my_data->argv[0] = stringdup(my_data->cli_argv);
				my_data->argv[1] = NULL;
			}
		}
		idx = 0;
		while (my_data->argv != NULL && my_data->argv[idx] != NULL)
			idx++;
		my_data->argc = idx;
	}
}


/**
 * chained_cmd_buff - Buffers input with chained commands
 * @my_data: A pointer to data_hub struct
 * @chained_buf: A string of arrays of input buffer
 * @buf_length: A pointer to the length of input buffer
 * Return: Number of bytes read
*/
ssize_t chained_cmd_buff(data_hub *my_data, char **chained_buf,
								size_t *buf_length)
{
	ssize_t bytes_read = 0;
	size_t gline_length = 0;

	if (!*buf_length) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)my_data->cmd_buf);*/
		free(*chained_buf);
		*chained_buf = NULL;
		signal(SIGINT, sigint_func);
#if GETLINE_SWITCH
		bytes_read = getline(chained_buf, &gline_length, stdin);
#else
		bytes_read = shell_getline(my_data, chained_buf, &gline_length);
#endif
		if (bytes_read > 0)
		{
			if ((*chained_buf)[bytes_read - 1] == '\n')
			{
				(*chained_buf)[bytes_read - 1] = '\0';
				bytes_read -= 1;
			}
			my_data->line_flagger = 1;
			comment_handler(*chained_buf);

			shell_history_list(my_data, *chained_buf, my_data->history_line_count++);
			{
				*buf_length = bytes_read;
				my_data->command_buffer = chained_buf;
			}
		}
	}
	return (bytes_read);
}


/**
 * sigint_func - Handles ctrl-c command
 * @signal_no: Signal number
*/

void sigint_func(__attribute__((unused))int signal_no)
{
	cust_puts("\n");
	cust_puts("$^[ ");
	put_char(EMPTY_BUFFER);
}


/**
 * shell_getline - Custom getline function
 * @my_data: Pointer to data_hub struct
 * @line_ptr: A pointer to a pointer to a character buffer
 * @size: Buffer size
 * Return: Length of the string stored in buffer (buffer_len)
*/

int shell_getline(data_hub *my_data, char **line_ptr, size_t *size)
{
	static char line_buffer[BUFFER_SIZE_R];
	static size_t track, length;
	size_t gline_len;
	ssize_t ret_value = 0, buf_size = 0;
	char *current_buf = NULL, *realloc_buff = NULL, *ch;

	current_buf = *line_ptr;
	if (current_buf && size)
		buf_size = *size;
	if (track == length)
		track = length = 0;

	ret_value = read_stdin(my_data, line_buffer, &length);
	if (ret_value == -1 || (ret_value == 0 && length == 0))
		return (-1);

	ch = find_char(line_buffer + track, '\n');
	if (ch != NULL)
		gline_len = 1 + (unsigned int)(ch - line_buffer);
	else
	    gline_len = length;

	realloc_buff = shell_realloc(current_buf, buf_size, buf_size ?
								buf_size + gline_len : gline_len + 1);
	if (realloc_buff == NULL)
		return (current_buf ? free(current_buf), -1 : -1);

	if (buf_size)
		string_n_concat(realloc_buff, line_buffer + track, gline_len - track);
	else
		string_n_copy(realloc_buff, line_buffer + track, gline_len - track + 1);

	buf_size += gline_len - track;
	track = gline_len;
	current_buf = realloc_buff;

	if (size)
		*size = buf_size;
	*line_ptr = current_buf;
	return (buf_size);
}


