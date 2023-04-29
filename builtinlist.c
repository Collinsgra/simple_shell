#include "shell.h"

/**
 * _shellexit - exits the shell
 * @info: constants function and arguments
 *  Return: exits
 */
int _shellexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])
	{
		exitcheck = error_asc(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Restricted number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = error_asc(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _shellcd - changes the current directory
 * @info: Struct ,functions and args
 *  Return: Always 0
 */
int _shellcd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = gt_environ(info, "HOME=");
		if (!dir)
			chdir_ret =
				chdir((dir = gt_environ(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (compare_string(info->argv[1], "-") == 0)
	{
		if (!gt_environ(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(gt_environ(info, "OLDPWD=")), _putchar('\n');
		chdir_ret =
			chdir((dir = gt_environ(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "cannot cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		set_environ(info, "OLDPWD", gt_environ(info, "PWD="));
		set_environ(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _shellhelp - help status
 * @info: Struct ,functions and args
 *  Return: Always 0
 */
int _shellhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("not yet available \n");
	if (0)
		_puts(*arg_array);
	return (0);
}
