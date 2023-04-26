#include "shell.h"

/**
 * builtinlist - search for same command and run the same builtin
 * @data: program's data struct
 * Return: return the function executed if there is a match,else return -1
 **/
int builtinlist(program_datas *data)
{
	int succession;
	builtins options[] = {
		{"exit", exit_builtin},
		{"help", help_builtin},
		{"cd", cd_builtin},
		{"alias", alias_builtin},
		{"env", env_builtin},
		{"setenv", set_env_builtin},
		{"unsetenv", unset_env_builtin},
		{NULL, NULL}
	};


	for (succession = 0; options[succession].builtin != NULL; succession++)
	{

		if (string_compare(options[succession].builtin, data->command_in, 0))
		{

			return (options[succession].function(data));
		}

	}
	return (-1);
}
