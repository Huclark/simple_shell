#include "shell.h"

/**
* shell_env - Retrieves a copy of the environ array
* @head: A pointer to the head of env_list
* Return: An array of strings of the environ
*/
char **shell_env(env_list **head)
{
	int no_of_env = 0, idx = 0;
	char **envp_cpy;
	env_list *node_ptr = *head;

	while (node_ptr != NULL)
	{
		node_ptr = node_ptr->next;
		no_of_env++;
	}

	envp_cpy = (char **)malloc(sizeof(char *) * (no_of_env + 1));

	if (envp_cpy == NULL)
	{
		perror("Memory allocation failed for environ copy");
		exit(EXIT_FAILURE);
	}

	node_ptr = *head;

	while (node_ptr != NULL)
	{
		envp_cpy[idx] = (char *)malloc(stringlength(node_ptr->var_name) +
							stringlength(node_ptr->var_value) + 2);
		if (envp_cpy[idx] == NULL)
		{
			perror("Failed to allocate memory for environ copy");
			exit(EXIT_FAILURE);
		}
		stringcopy(envp_cpy[idx], node_ptr->var_name);
		stringconcat(envp_cpy[idx], "=");
		stringconcat(envp_cpy[idx], node_ptr->var_value);
		idx++;
		node_ptr = node_ptr->next;
	}
	envp_cpy[idx] = NULL;
	return (envp_cpy);
}


/**
* shell_getenv - Retrieves the value of an environ variable by looping
*                through the environ array.
* @var_name: Environment variable prefix
* @head: A pointer to the head of env_list
* Return: The environment variable's value
*/
char *shell_getenv(env_list **head, char *var_name)
{
	env_list *node_ptr = *head;

	if (!var_name || !environ)
		return (NULL);

	while (node_ptr != NULL)
	{
		if (stringcompare(node_ptr->var_name, var_name) == 0)
			return (node_ptr->var_value);
		node_ptr = node_ptr->next;
	}
	return (NULL);
}


/**
* shell_setenv - Creates or updates the value of an environment variable
* @head: Pointer to the head of env_list linked list
* @var_name: The environment variable to update or create
* @var_value: The value to assign to the environment variable
* @flag: Flag. 1 means update value to new value. 0 means do not flag
* Return: 0 on success or -1 if otherwise
*/
int shell_setenv(env_list **head, char *var_name, char *var_value, int flag)
{
	env_list *node_ptr = *head, *prev_node = NULL, *new_var;

	while (node_ptr != NULL) /* Check if environment variable exists */
	{
		if (stringcompare(node_ptr->var_name, var_name) == 0)
		{
			if (!flag) /* If false then do nothing */
				return (0);

			else /* If true then overwrite */
			{
				node_ptr->var_value = var_value;
				return (0);
			}
		}
		prev_node = node_ptr;
		node_ptr = node_ptr->next;
	}

	/* It does not exist. Create a new one */
	new_var = (env_list *)malloc(sizeof(env_list));
	if (new_var == NULL)
	{
		perror("Memory allocation failed");
		return (-1);
	}
	new_var->var_name = var_name;
	new_var->var_value = var_value;
	new_var->next = NULL;

	if (prev_node != NULL)
		prev_node->next = new_var;
	else
		*head = new_var;

	return (0);
}


/**
 * env_list_init - Initializes env_list linked list
 * @environ: Array of environment variable strings
 * Return: A pointer to the env_list
*/
env_list *env_list_init(char **environ)
{
	env_list *head = NULL, *node_ptr = NULL, *new_node = NULL;
	char *env_ptr;
	int idx = 0;

	while (environ[idx] != NULL)
	{
		new_node = (env_list *)malloc(sizeof(env_list));
		if (new_node == NULL)
		{
			perror("Memory allocation failed");
			exit(EXIT_FAILURE);
		}

		env_ptr = environ[idx];
		new_node->var_name = strtok(env_ptr, "=");
		new_node->var_value = strtok(NULL, "=");
		new_node->next = NULL;

		if (head == NULL)
		{
			head = new_node;
			node_ptr = head;
		}

		else
		{
			node_ptr->next = new_node;
			node_ptr = new_node;
		}
		idx++;
	}
	return (head);
}




