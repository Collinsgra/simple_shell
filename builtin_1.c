#include "shell.h"

/**
 * shellHistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int shellHistory(info_t *info)
{
	listPrinted(info->history);
	return (0);
}

/**
 * unset_alias - aliases to strs
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0, else 1
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = chars_str(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = remove_data(&(info->alias),
		receiveData(info->alias, dt_begins_at(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - aliases to strs
 * @info: structure
 * @str: str aliases
 *
 * Return: Always 0, else 1
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = chars_str(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_poss_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @data: data of aliases
 *
 * Return: Always 0, else 1
 */
int print_alias(list_t *data)
{
	char *p = NULL, *a = NULL;

	if (data)
	{
		p = chars_str(data->str, '=');
		for (a = data->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * shellAlias - man alias
 * @info: Struct ,functions and args
 *  Return: Always 0
 */
int shellAlias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *data = NULL;

	if (info->argc == 1)
	{
		data = info->alias;
		while (data)
		{
			print_alias(data);
			data = data->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = chars_str(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(dt_begins_at(info->alias, info->argv[i], '='));
	}

	return (0);
}
