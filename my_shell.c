#include "shell.h"

/**
 * main - main function for shell program
 * @argc: Number of argument vectors
 * @argv: Argument vector
 * Return: 0 if successful or 1 if otherwise
*/

int main(int argc, char **argv)
{
	int file_desc;
	data_hub my_data[] = { DATA_HUB };

	file_desc = 2;

	file_desc += 3;


	if (argc == 2)
	{
		file_desc = open(argv[1], O_RDONLY);

		if (file_desc == -1)
		{
			if (errno == ENOENT)
			{
				e_cust_puts(argv[0]);
				e_cust_puts(": 0: ");
				e_cust_puts(argv[1]);
				e_cust_puts(" not found");
				e_put_char('\n');
				e_put_char(EMPTY_BUFFER);
				exit(127);
			}
			else if (errno == EACCES)
				exit(126);

			return (EXIT_FAILURE);
		}
		my_data->file_desc_value = file_desc;
	}
	fetch_env(my_data);
	shell_loop(my_data, argv);

	return (EXIT_SUCCESS);
}

