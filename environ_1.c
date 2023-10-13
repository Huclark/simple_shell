#include "shell.h"

/**
* shell_env - Retrieves a copy of the environ array
* Return: An array of strings of the environ
*/
char **shell_env(void)
{
	int no_of_env = 0, idx = 0;
	char **envp_cpy;

	while (environ[no_of_env] != NULL)
		no_of_env++;

	envp_cpy = (char **)malloc(sizeof(char *) * (no_of_env + 1));

	if (envp_cpy == NULL)
	{
		perror("Memory allocation failed for environ copy");
		exit(EXIT_FAILURE);
	}

	while (environ[idx] != NULL)
	{
		envp_cpy[idx] = stringdup(environ[idx]);
		if (envp_cpy[idx] == NULL)
		{
			perror("Memory allocation failed for environ copy");
			exit(EXIT_FAILURE);
		}
		idx++;
	}
	envp_cpy[idx] = NULL;
	return (envp_cpy);
}


/**
* shell_getenv - Retrieves the value of an environ variable by looping
*                through the environ array.
* @var_name: Environment variable prefix
* Return: The environment variable's value
*/
char *shell_getenv(char *var_name)
{
	int idx = 0;

	if (!var_name || !environ)
		return (NULL);

	while (environ[idx] != NULL)
	{
		if (string_n_cmp(environ[idx], var_name,
			stringlength(var_name)) == 0 && environ[idx][stringlength(var_name)] == '=')
			return (environ[idx] + stringlength(var_name) + 1);
		idx++;
	}
	return (NULL);
}


/**
* shell_setenv - Creates or updates the value of an environment variable
* @var_name: The environment variable to update or create
* @value: The value to assign to the environment variable
* @flag: Flag. 1 means update value to new value. 0 means do not flag
* Return: 0 on success or -1 if otherwise
*/
int shell_setenv(char *var_name, char *value, int flag)
{
	char *new_var, *existing;

	if (var_name == NULL || value == NULL)
		return (-1);

	/* Create string for environment variable */
	new_var = create_env_string(var_name, value);

	if (new_var == NULL)
		return (-1);

	/* Check if the environment variable already exists */
	existing = shell_getenv(var_name);

	if (existing != NULL)
	{
		/* If flag = 0, do nothing */
		if (!flag)
		{
			free(new_var);
			return (0);
		}
		/* If flag = 1, remove the existing variable */
		shell_unsetenv(var_name);
	}

	/* Add the new environment variable */
	if (add_shell_env(var_name, value) != 0)
	{
		free(new_var);
		return (-1);
	}

	return (0);
}


/**
* add_shell_env - Handles the addition or replacement of environment variables
* @var_name: Environment variable to add or replace
* @value: The environment variable's value
* Return: 0 on success or -1 if otherwise
*/
int add_shell_env(char *var_name, char *value)
{
	char *new_var, **new_environ;
	int var_idx, i, env_count = 0;

	if (!var_name || !value)
		return (-1);
	new_var = create_env_string(var_name, value); /* Create new env */

	if (!new_var)
		return (-1);
	var_idx = check_env_exist(var_name); /* Check if env exists */

	if (var_idx != 0) /* non-zero means exists so replace it */
	{
		free(environ[var_idx]);
		environ[var_idx] = new_var;
	}
	else /* does not exist */
	{
		while (environ[env_count] != NULL) /* count number of environs */
			env_count++;
		new_environ = (char **)malloc((env_count + 2) * sizeof(char *));

		if (!new_environ)
		{
			perror("Memory allocation failed");
			free(new_var);
			return (-1);
		}
		/* Copy existing environs to new array */
		for (i = 0 ; i < env_count ; i++)
			new_environ[i] = environ[i];
		/* Add new environ to end of array */
		new_environ[env_count] = new_var;
		new_environ[env_count + 1] = NULL;

		free(environ);
		environ = new_environ;  /* Replace old environ with new environ */
	}
	return (0);
}


/**
* check_env_exist - Checks if environment variable exists
* @var_name: Environment variable string
* Return: i if env variable exists or 0 if otherwise
*/
int check_env_exist(char *var_name)
{
	int i;

	if (var_name == NULL)
		return (0);

	 /* Check if env variable exists */
	for (i = 0; environ[i] != NULL; i++)

	{
		if (string_n_cmp(environ[i], var_name, stringlength(var_name)) == 0 &&
			environ[i][stringlength(var_name)] == '=')
		{
			return (i); /* Env variable exists */
		}
	}
	return (0); /* Env variable does not exist */
}




