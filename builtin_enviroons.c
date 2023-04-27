#include "shell.h"

/**
 * env_builtin - shows the env wher bash runs
 * @data: program's data structures
 * Return: 0 if success, or other number if declared args
 */
int builtin_env(program_datas *data)
{
	int i;
	char cpname[50] = {'\0'};
	char *var_copy = NULL;


	if (data->toks[1] == NULL)
		print_environ(data);
	else
	{
		for (i = 0; data->toks[1][i]; i++)
		{
			if (data->toks[1][i] == '=')
			{
				var_copy = string_dup(environ_get_key(cpname, data));
				if (var_copy != NULL)
					environ_get_key(cpname, data->toks[1] + i + 1, data);


				print_environ(data);
				if (environ_get_key(cpname, data) == NULL)
				{
					_print(data->toks[1]);
					_print("\n");
				}
				else
				{
					environ_set_key(cpname, var_copy, data);
					free(var_copy);
				}
				return (0);
			}
			cpname[i] = data->toks[1][i];
		}
		errno = 2;
		perror(data->command_in);
		errno = 127;
	}
	return (0);
}

/**
 * builtin_set_env - ..
 * @data: struct for the program's data
 * Return: 0 if success, or other number if declared args
 */
int builtin_set_env(program_datas *data)
{

	if (data->toks[1] == NULL || data->toks[2] == NULL)
		return (0);
	if (data->toks[3] != NULL)
	{
		errno = E2BIG;
		perror(data->command_in);
		return (5);
	}

	environ_get_key(data->toks[1], data->toks[2], data);

	return (0);
}

/**
 * unset_env_builtin - Unsets the env
 * @data: program's data structures
 * Return: ..
 */
int builtin_unset_env(program_datas *data)
{

	if (data->toks[1] == NULL)
		return (0);
	if (data->toks[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_in);
		return (5);
	}
	environ_remove_key(data->toks[1], data);

	return (0);
}
