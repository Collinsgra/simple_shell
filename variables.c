#include "shell.h"

/**
 * equal_to_chain - test if current buffer
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int equal_to_chain(info_t *info, char *buf, size_t *p)
{
	size_t x = *p;

	if (buf[x] == '|' && buf[x + 1] == '|')
	{
		buf[x] = 0;
		x++;
		info->command_typ_buffer = CMD_OR;
	}
	else if (buf[x] == '&' && buf[x + 1] == '&')
	{
		buf[x] = 0;
		x++;
		info->command_typ_buffer = CMD_AND;
	}
	else if (buf[x] == ';') /* found end of this command */
	{
		buf[x] = 0; /* replace semicolon with null */
		info->command_typ_buffer = CMD_CHAIN;
	}
	else
		return (0);
	*p = x;
	return (1);
}

/**
 * _checker - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void _checker(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t x = *p;

	if (info->command_typ_buffer == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			x = len;
		}
	}
	if (info->command_typ_buffer == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			x = len;
		}
	}

	*p = x;
}

/**
 * alias_displace - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int alias_displace(info_t *info)
{
	int i;
	list_t *data;
	char *p;

	for (i = 0; i < 10; i++)
	{
		data = dt_begins_at(info->alias, info->argv[0], '=');
		if (!data)
			return (0);
		free(info->argv[0]);
		p = chars_str(data->str, '=');
		if (!p)
			return (0);
		p = string_duplicate(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * rep_variables - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rep_variables(info_t *info)
{
	int i = 0;
	list_t *data;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!compare_string(info->argv[i], "$?"))
		{
			str_rep(&(info->argv[i]),
				string_duplicate(changeNum(info->status, 10, 0)));
			continue;
		}
		if (!compare_string(info->argv[i], "$$"))
		{
			str_rep(&(info->argv[i]),
				string_duplicate(changeNum(getpid(), 10, 0)));
			continue;
		}
		data = dt_begins_at(info->env, &info->argv[i][1], '=');
		if (data)
		{
			str_rep(&(info->argv[i]),
				string_duplicate(chars_str(data->str, '=') + 1));
			continue;
		}
		str_rep(&info->argv[i], string_duplicate(""));

	}
	return (0);
}

/**
 * str_rep - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1, else 0
 */
int str_rep(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
