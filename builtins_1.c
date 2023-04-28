#include "shell.h"

/**
 * builtin_exit - exit of the program with the status
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int builtin_exit(program_datas *data)
{
	int i;

	if (data->toks[1] != NULL)
	{
		for (i = 0; data->toks[1][i]; i++)
			if ((data->toks[1][i] < '0' || data->toks[1][i] > '9')
				&& data->toks[1][i] != '+')
			{
				errno = 2;
				return (2);
			}
		errno = _atoi(data->toks[1]);
	}
	free_all_data(data);
	exit(errno);
}

/**
 * cd_builtin - change directory
 * @data: program's data struct
 * Return: 0 if success, or other if declared in args
 */
int builtin_cd(program_datas *data)
{
	char *dir_home = environ_get_key("HOME", data), *dir_old = NULL;
	char old_dir[128] = {0};
	int error_code = 0;

	if (data->toks[1])
	{
		if (string_compare(data->toks[1], "-", 0))
		{
			dir_old = environ_get_key("OLDPWD", data);
			if (dir_old)
				error_code = set_work_directory(data, dir_old);
			_print(environ_get_key("PWD", data));
			_print("\n");

			return (error_code);
		}
		else
		{
			return (set_work_directory(data, data->toks[1]));
		}
	}
	else
	{
		if (!dir_home)
			dir_home = getcwd(old_dir, 128);

		return (set_work_directory(data, dir_home));
	}
	return (0);
}

/**
 * set_work_directory - set the work directory
 * @data: struct for the program's data
 * @new_dir: path to be set as work directory
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int set_work_directory(program_datas *data, char *new_dir)
{
	char old_dir[128] = {0};
	int err_code = 0;

	getcwd(old_dir, 128);

	if (!string_compare(old_dir, new_dir, 0))
	{
		err_code = chdir(new_dir);
		if (err_code == -1)
		{
			errno = 2;
			return (3);
		}
		environ_set_key("PWD", new_dir, data);
	}
	environ_set_key("OLDPWD", old_dir, data);
	return (0);
}

/**
 * help_builtin - shows the environment where the shell runs
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int builtin_help(program_datas *data)
{
	int i, length = 0;
	char *text_display[6] = {NULL};

	text_display[0] = HELP_DET;

	/* validate args */
	if (data->toks[1] == NULL)
	{
		_print(text_display[0] + 6);
		return (1);
	}
	if (data->toks[2] != NULL)
	{
		errno = E2BIG;
		perror(data->name_progr);
		return (5);
	}
	text_display[1] = HELP_DET_EXIT;
	text_display[2] = HELP_DET_ENV;
	text_display[3] = HELP_DET_SETENV;
	text_display[4] = HELP_DET_UNSETENV;
	text_display[5] = HELP_DET_CD;

	for (i = 0; text_display[i]; i++)
	{
		length = string_length(data->toks[1]);
		if (string_compare(data->toks[1], text_display[i], length))
		{
			_print(text_display[i] + length + 1);
			return (1);
		}
	}

	errno = EINVAL;
	perror(data->command_in);
	return (0);
}

/**
 * builtin_alias - add, remove or show aliases
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int alias_builtin(program_datas *data)
{
	int i = 0;


	if (data->toks[1] == NULL)
		return (print_alias(data, NULL));

	while (data->toks[++i])
	{
		if (count_chars(data->toks[i], "="))
			set_alias(data->toks[i], data);
		else
			print_alias(data, data->toks[i]);
	}

	return (0);
}
