#include "shell.h"

/**
 * shellenv - current working environment
 * @info: functions
 * Return: Always 0
 */
int shellenv(info_t *info)
{
	string_prt_st(info->env);
	return (0);
}

/**
 * gt_environ - gets the value of an environ variable
 * @info: functions
 * @name: env var name
 *
 * Return: the value
 */
char *gt_environ(info_t *info, const char *name)
{
	list_t *data = info->env;
	char *p;

	while (data)
	{
		p = starts_with(data->str, name);
		if (p && *p)
			return (p);
		data = data->next;
	}
	return (NULL);
}

/**
 * shellsetenv - new or modify existing
 * @info: functions
 *  Return: Always 0
 */
int shellsetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Wrong number of arguments\n");
		return (1);
	}
	if (set_environ(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * shellunsetenv - delete an environment vars
 * @info: functions
 *  Return: Always 0
 */
int shellunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		unset_environ(info, info->argv[i]);

	return (0);
}

/**
 * multiply_list_of_env - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int multiply_list_of_env(info_t *info)
{
	list_t *data = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_poss_end(&data, environ[i], 0);
	info->env = data;
	return (0);
}
