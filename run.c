#include "shell.h"
/**
 * run - run a command with its entire path variables.
 * @data: a pointer to the program's data
 * Return: 0 (Success), else -1.
 */
int run(program_datas *data)
{
	int return_value = 0, status;
	pid_t pidd;


	return_value = builtinlist(data);
	if (return_value != -1)
		return (return_value);


	return_value = find_prog(data);
	if (return_value)
	{
		return (return_value);
	}
	else
	{
		pidd = fork();
		if (pidd == -1)
		{
			perror(data->command_in);
			exit(EXIT_FAILURE);
		}
		if (pidd == 0)
		{
			return_value = execve(data->toks[0], data->toks, data->environs);
			if (return_value == -1)
				perror(data->name_progr), exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
			if (WIFEXITED(status))
				errno = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				errno = 128 + WTERMSIG(status);
		}
	}
	return (0);
}
