#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = stringList(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * unset_environ - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int unset_environ(info_t *info, char *var)
{
	list_t *data = info->env;
	size_t i = 0;
	char *p;

	if (!data || !var)
		return (0);

	while (data)
	{
		p = starts_with(data->str, var);
		if (p && *p == '=')
		{
			info->env_changed = remove_data(&(info->env), i);
			i = 0;
			data = info->env;
			continue;
		}
		data = data->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * set_environ - Initialize a new evar
 * @info: function
 * @var: the string env var
 * @value: the string env var value
 *  Return: Always 0
 */
int set_environ(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *data;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(string__length(var) + string__length(value) + 2);
	if (!buf)
		return (1);
	copy_string(buf, var);
	string_conc(buf, "=");
	string_conc(buf, value);
	data = info->env;
	while (data)
	{
		p = starts_with(data->str, var);
		if (p && *p == '=')
		{
			free(data->str);
			data->str = buf;
			info->env_changed = 1;
			return (0);
		}
		data = data->next;
	}
	add_poss_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
