#include "shell.h"

/**
* create_env_string - Creates the name=value string
* @var_name: The environment variable to create
* @value: The value to assign to the environment variable
* Return: The new environment variable created or NULL
*/
char *create_env_string(char *var_name, char *value)
{
	/* Find length of name=value string */
	size_t name_len = stringlength(var_name);
	size_t value_len = stringlength(value);

	/* +1 for '=' and +1 for null terminator */
	char *new_var = (char *)malloc(name_len + 1 + value_len + 1);

	if (new_var == NULL)
	{
		perror("Memory allocation failed");
		return (NULL);
	}

	stringcopy(new_var, var_name);

	/* Add the '=' character */
	new_var[name_len] = '=';

	/* Copy the value into the new variable */
	stringcopy(new_var + name_len + 1, value);

	return (new_var);
}


/**
* shell_unsetenv - Searches for the environment variable
* @var_name: The environment variable to create
* Return: 0 on success or -1 on failure
*/
int shell_unsetenv(char *var_name)
{
	int flag, idx, i;

	if (!var_name || !environ)
		return (-1);

	flag = -1; /* Initialize to -1 to first indicate not found */

	/* Find environment variable */
	for (idx = 0 ; environ[idx] != NULL ; idx++)
	{
		if (string_n_cmp(environ[idx], var_name, stringlength(var_name)) == 0 &&
			environ[idx][stringlength(var_name)] == '=')
		{
			flag = idx;
			break;
		}
	}
	if (flag == -1) /* Environment variable not found */
		return (0);
	for (i = flag ; environ[i] != NULL ; i++)
		environ[i] = environ[i + 1];

	return (0);
}


/**
* find_command - Searches PATH to find the full path to the executable command
* @argv_tkn: Array of nulll-terminated tokens
* Return: The full path to command or Null if command is not found
*/
char *find_command(char **argv_tkn)
{
	char *cmd_dir, *cmd_path, *path_cpy, *path = shell_getenv("PATH");

	if (find_char(argv_tkn[0], '/') != NULL)
	{
		cmd_path = stringdup(argv_tkn[0]);
		if (cmd_path == NULL)
			return (NULL);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
	}
	else
	{
		cmd_path = malloc(stringlength(argv_tkn[0]) + 3);
		if (cmd_path == NULL)
			return (NULL);
		stringcopy(cmd_path, "./");
		stringconcat(cmd_path, argv_tkn[0]);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		if (path == NULL)
			return (NULL);
		path_cpy = stringdup(path);
		if (path_cpy == NULL)
			return (NULL);
		cmd_dir = strtok_delims(path_cpy, ":");
		while (cmd_dir != NULL)
		{
			cmd_path = find_exec_in_path(cmd_dir, argv_tkn[0]);
			if (cmd_path != NULL)
			{
				free(path_cpy);
				return (cmd_path);
			}
			cmd_dir = strtok_delims(NULL, ":");
		}
		free(path_cpy);
	}
	return (NULL);
}


/**
 * find_exec_in_path - Finds an executable in path
 * @dir: The directory to search
 * @command: The command to find
 * Return: The full path to the command if found or NULL if otherwise
*/
char *find_exec_in_path(char *dir, char *command)
{
	char *cmd_path = malloc(stringlength(dir) + stringlength(command) + 2);

	if (cmd_path == NULL)
		return (NULL);

	stringcopy(cmd_path, dir);
	stringconcat(cmd_path, "/");
	stringconcat(cmd_path, command);

	if (access(cmd_path, X_OK) == 0)
		return (cmd_path);

	free(cmd_path);
	return (NULL);
}



