#include "shell.h"

/**
 * retrieve_env_var - Generates environmental variables
 * @my_data: pointer to data_hub struct. Passes the relevant arguments
 *           to function.
 * Return: environmental variable
*/

char **retrieve_env_var(data_hub *my_data)
{
	if (my_data->env_flag != 0 || !my_data->child_env)
	{
		my_data->env_flag = 0;
		my_data->child_env = shell_list_strings(my_data->shell_env);
	}
	return (my_data->child_env);
}


/**
 * get_matching_env_variable - Retrieves the environment variable to be used
 * @my_data: A pointer to the data_hub struct
 * @environ_to_use: Environment variable to use
 * Return: A pointer to the environmental to use
 *         Or NULL if not found
*/

char *get_matching_env_variable(const char *environ_to_use, data_hub *my_data)
{
	shell_lst *traverse = my_data->shell_env;
	char *env_ptr;

	while (traverse != NULL)
	{
		env_ptr = prefix_checker(environ_to_use, traverse->string);

		if (env_ptr != NULL && *env_ptr != '\0')
			return (env_ptr);
		traverse = traverse->link_node;
	}

	return (NULL);
}


/**
 * build_env - Modifies an environment variable
 *             Or creates a new one if it is non-existent
 * @my_data: A pointer to the data_hub struct
 * @env_prop: The environment variable property string
 * @env_value: The environment variable value
 * Return: 0 on success
 *         1 on failure
*/
int build_env(data_hub *my_data, char *env_prop, char *env_value)
{
	char *env_buffer = NULL;
	shell_lst *env_node;
	char *env_ptr;

	if (env_prop == NULL || env_value == NULL)
		return (0);

	env_buffer = malloc(stringlength(env_prop) + stringlength(env_value) + 2);
	if (env_buffer == NULL)
		return (1);
	stringcopy(env_buffer, env_prop);
	stringconcat(env_buffer, "=");
	stringconcat(env_buffer, env_value);

	env_node = my_data->shell_env;
	while (env_node != NULL)
	{
		env_ptr = prefix_checker(env_prop, env_node->string);
		if (env_ptr != NULL && *env_ptr == '=')
		{
			free(env_node->string);
			env_node->string = env_buffer;
			my_data->env_flag = 1;
			return (0);
		}
		env_node = env_node->link_node;
	}

	add_shell_list_end(&(my_data->shell_env), env_buffer, 0);
	free(env_buffer);
	my_data->env_flag = 1;

	return (0);
}


/**
 * fetch_env - Handles shell_list for environment variables
 * @my_data: A pointer to data_hub struct
 * Return: 0 on success
*/

int fetch_env(data_hub *my_data)
{
	shell_lst *node_ptr = NULL;
	size_t idx = 0;

	while (environ[idx])
	{
		add_shell_list_end(&node_ptr, environ[idx], 0);
		idx++;
	}

	my_data->shell_env = node_ptr;

	return (0);
}


