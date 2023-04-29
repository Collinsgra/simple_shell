#include "shell.h"

/**
 * wipeInfo - initializes wipeinfo struct
 * @info: struct address
 */
void wipeInfo(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * makeInformation - initializesmakeing=fo struct
 * @info: struct address
 * @av: argument vector
 */
void makeInformation(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = string_to_words(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = string_duplicate(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		alias_displace(info);
		rep_variables(info);
	}
}

/**
 * allow_info - frees allow_info struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void allow_info(info_t *info, int all)
{
	free_str_str(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		free_str_str(info->environ);
			info->environ = NULL;
		free_ptr((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
