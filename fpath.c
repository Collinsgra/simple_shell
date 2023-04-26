#include "shell.h"

int check_doc(char *full_path);

/**
 * find_prog - finding a program in the path
 * @data: a pointer to the program's data
 * Return: 0 if success, errcode otherwise
 */

int find_prog(program_datas *data)
{
	int i = 0, retturn_code = 0;
	char **directories;

	if (!data->command_in)
		return (2);

	/**if is a full_path or an executable in the same path */
	if (data->command_in[0] == '/' || data->command_in[0] == '.')
		return (check_doc(data->command_in));

	free(data->toks[0]);
	data->toks[0] = string_concat(string_dup("/"), data->command_in);
	if (!data->toks[0])
		return (2);

	directories = tokenize_path(data);/* search in the PATH */

	if (!directories || !directories[0])
	{
		errno = 127;
		return (127);
	}
	for (i = 0; directories[i]; i++)
	{
		directories[i] = string_concat(directories[i], data->toks[0]);
		retturn_code = check_doc(directories[i]);
		if (retturn_code == 0 || retturn_code == 126)
		{
			errno = 0;
			free(data->toks[0]);
			data->toks[0] = string_dup(directories[i]);
			free_array_of_pointers(directories);
			return (retturn_code);
		}
	}
	free(data->toks[0]);
	data->toks[0] = NULL;
	free_array_of_pointers(directories);
	return (retturn_code);
}

/**
 * tokenize_path - tokenize the path in directories
 * @data: a pointer to the program's data
 * Return: array of path directories
 */

char **tokenize_path(program_datas *data)
{
	int i = 0;
	int counter_directories = 2;
	char **toks = NULL;
	char *PATH;


	PATH = environ_get_key("PATH", data);
	if ((PATH == NULL) || PATH[0] == '\0')
	{
		return (NULL);
	}

	PATH = string_dup(PATH);


	for (i = 0; PATH[i]; i++)
	{
		if (PATH[i] == ':')
			counter_directories++;
	}


	toks = malloc(sizeof(char *) * counter_directories);


	i = 0;
	toks[i] = string_dup(_strtok(PATH, ":"));
	while (toks[i++])
	{
		toks[i] = string_dup(_strtok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (toks);

}

/**
 * check_doc - checks if a doc it exists, if it isn't a directory and
 * if it has permision for executions.
 * @full_path: pointer to the full doc name
 * Return: 0 on success, or error code if it exists.
 */

int check_doc(char *full_path)
{
	struct stat ab;

	if (stat(full_path, &ab) != -1)
	{
		if (S_ISDIR(ab.st_mode) ||  access(full_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}

	errno = 127;
	return (127);
}
