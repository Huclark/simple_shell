#include "shell.h"

/**
 * cmd_checker - Checks if a file to execute is actually
 *               an executable command
 * @filename: A pointer to the name of file to execute
 * @my_data: A pointer to data_hub struct
 * Return: 1 if file is an executable command
 *         0 if otherwise
*/

int cmd_checker(char *filename, data_hub *my_data)
{
	struct stat file_info;

	(void)my_data;

	if (!filename || stat(filename, &file_info))
		return (0);

	if (file_info.st_mode & S_IFREG)
		return (1);

	return (0);
}


/**
 * shell_cd - Replicates the cd command in shell
 * @my_data: A pointer to the data_hub struct
 * Return: 0 on success
*/

int shell_cd(data_hub *my_data)
{
	char buf[1024], *cwd_pathname = getcwd(buf, 1024), *cwd;
	int ret;

	if (cwd_pathname == NULL)
		cust_puts("No such file or directory\n");
	if (my_data->argv[1] == NULL)
	{
		cwd = get_matching_env_variable("HOME=", my_data);
		if (cwd == NULL)
			ret = chdir((cwd = get_matching_env_variable("PWD=", my_data)) ? cwd : "/");
		else
			ret = chdir(cwd);
	}
	else if (stringcompare("-", my_data->argv[1]) == 0)
	{
		if (get_matching_env_variable("OLDPWD=", my_data) == NULL)
		{
			cust_puts(cwd_pathname), put_char('\n');
			return (1);
		}
		e_cust_puts(get_matching_env_variable("OLDPWD=", my_data)), put_char('\n');
		cwd = get_matching_env_variable("OLDPWD=", my_data);
		if (cwd != NULL)
			ret = chdir(cwd);
		else
			ret = chdir("/");
	}
	else
		ret = chdir(my_data->argv[1]);
	if (ret == -1)
	{
		error_output(my_data, "can not cd to ");
		e_cust_puts(my_data->argv[1]), e_put_char('\n');
	}
	else
	{
		build_env(my_data, "OLDPWD", get_matching_env_variable("PWD=", my_data));
		build_env(my_data, "PWD", getcwd(buf, 1023));
	}
	return (0);
}


/**
 * cmd_in_path - Locates the command in the the PATH string
 * @my_data: A pointer to the data_hub struct
 * @stringpath: The PATH
 * @command:  The command to search for
 * Return: The PATH of the command found
 *         Or NULL if comand is not found
*/
char *cmd_in_path(data_hub *my_data, char *stringpath, char *command)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!stringpath)
		return (NULL);
	if ((stringlength(command) > 2) && prefix_checker("./", stringpath))
	{
		if (cmd_checker(command, my_data))
			return (command);
	}
	while (1)
	{
		if (!stringpath[i] || stringpath[i] == ':')
		{
			path = pathstring_cpy(stringpath, curr_pos, i);
			if (!*path)
				stringconcat(path, command);
			else
			{
				stringconcat(path, "/");
				stringconcat(path, command);
			}
			if (cmd_checker(path, my_data))
				return (path);
			if (!stringpath[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}


