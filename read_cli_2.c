#include "shell.h"

/**
 * read_stdin - reads line from stdin
 * @my_data: A pointer to the data_hub struct
 * @buf_to_read: Buffer to read
 * @buf_size: Buffer size
 * Return: Return value of read()
*/

ssize_t read_stdin(data_hub *my_data, char *buf_to_read, size_t *buf_size)
{
	ssize_t ret_value = 0;

	if (*buf_size)
		return (0);
	ret_value = read(my_data->check_file_desc, buf_to_read, BUFFER_SIZE_R);
	if (ret_value >= 0)
		*buf_size = ret_value;
	return (ret_value);
}


/**
 * comment_handler - Handles comments (#) by replacing them
 *                   this a null character '\0'
 * @line_bfr: String input
*/

void comment_handler(char *line_bfr)
{
	int idx = 0;

	while (line_bfr[idx] != '\0')
	{
		if (line_bfr[idx] == '#' && (!idx || line_bfr[idx - 1] == ' '))
		{
			line_bfr[idx] = '\0';
			break;
		}
		idx += 1;
	}
}


/**
 * upd_chain - Determines whether to continue chaining commands
 *             depending on the last command's exit status
 * @my_data: A pointer to data_hub struct
 * @buffer: Buffer
 * @curr_idx: A pointer to the current index in buffer
 * @starting_idx: The starting position
 * @buff_length: Buffer length
*/

void upd_chain(data_hub *my_data, char *buffer, size_t *curr_idx,
					size_t starting_idx, size_t buff_length)
{
	size_t idx_ptr = *curr_idx;

	if (my_data->cmd_mode == AND_COMMAND)
	{
		if (my_data->return_stats)
		{
			buffer[starting_idx] = 0;
			idx_ptr = buff_length;
		}
	}
	if (my_data->cmd_mode == OR_COMMAND)
	{
		if (!my_data->return_stats)
		{
			buffer[starting_idx] = 0;
			idx_ptr = buff_length;
		}
	}

	*curr_idx = idx_ptr;
}


/**
 * chain_test - Determines whether a character is a chain delimiter (||, &&, ;)
 * @my_data: A pointer to data_hub struct
 * @ch_buff: A character buffer containingt the command line or input
 * @curr_idx: A pointer to the current position in the buffer
 * Return: 1 if chain delimiter is detected
 *         o if no chain delimimter is found
*/

int chain_test(data_hub *my_data, char *ch_buff, size_t *curr_idx)
{
	size_t idx_ptr = *curr_idx;

	if (ch_buff[idx_ptr] == '|' && ch_buff[idx_ptr + 1] == '|')
	{
		ch_buff[idx_ptr] = 0;
		idx_ptr++;
		my_data->cmd_mode = OR_COMMAND;
	}
	else if (ch_buff[idx_ptr] == '&' && ch_buff[idx_ptr + 1] == '&')
	{
		ch_buff[idx_ptr] = 0;
		idx_ptr++;
		my_data->cmd_mode = AND_COMMAND;
	}
	else if (ch_buff[idx_ptr] == ';')
	{
		ch_buff[idx_ptr] = 0;
		my_data->cmd_mode = SEPARATOR_COMMAND;
	}
	else
		return (0);
	*curr_idx = idx_ptr;
	return (1);
}

