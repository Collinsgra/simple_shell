#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		wipeInfo(info);
		if (reciprocal(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = gt_inpuutt(info);
		if (r != -1)
		{
			makeInformation(info, av);
			builtin_ret = builtin_checker_file(info);
			if (builtin_ret == -1)
				find_a_command(info);
		}
		else if (reciprocal(info))
			_putchar('\n');
		allow_info(info, 0);
	}
	write_history(info);
	allow_info(info, 1);
	if (!reciprocal(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * builtin_checker_file - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int builtin_checker_file(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _shellexit},
		{"env", shellenv},
		{"help", _shellhelp},
		{"history", shellHistory},
		{"setenv", shellsetenv},
		{"unsetenv", shellunsetenv},
		{"cd", _shellcd},
		{"alias", shellAlias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (compare_string(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_a_command - finding command
 * @info: the paraminfo struct
 *
 * Return: void
 */
void find_a_command(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->totalLns_cnt_flag == 1)
	{
		info->line_count++;
		info->totalLns_cnt_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!limiter_de_fe(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = check_path(info, gt_environ(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		func_fork(info);
	}
	else
	{
		if ((reciprocal(info) || gt_environ(info, "PATH=")
			|| info->argv[0][0] == '/') && cmd_cln(info, info->argv[0]))
			func_fork(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * func_fork - forks executable thread
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void func_fork(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{

		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			allow_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}

	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Access denied\n");
		}
	}
}
