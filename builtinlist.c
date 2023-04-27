#include "shell.h"

/**
 * builtinlist - search for same command and run the same builtin
 * @data: program's data struct
 * Return: return the function executed if there is a match,else return -1
 **/
int builtinlist(program_datas *data)
{
	int succession;
	_builtins options[] = {


		{"exit", builtin_exit},
		{"help", builtin_help},
		{"cd", builtin_cd},
		{"alias", builtin_alias},
		{"env", builtin_env},
		{"setenv", builtin_set_env},
		{"unsetenv", builtin_unset_env},
		{NULL, NULL}
	};


	for (succession = 0; options[succession].builtins != NULL; succession++)
	{

		if (string_compare(options[succession].builtins, data->command_in, 0))
		{

			return (options[succession].function(data));
		}

	}
	return (-1);
}
