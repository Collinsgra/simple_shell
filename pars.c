#include "shell.h"

/**
 * cmd_cln - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int cmd_cln(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * chars_clone - clones
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer
 */
char *chars_clone(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * check_path - finds cmd
 * @info: info struct
 * @pathstr: PATH string
 * @cmd: the cmd to be found
 *
 * Return: NULL ,full path of cmd if found or 
 */
char *check_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((string__length(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (cmd_cln(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = chars_clone(pathstr, curr_pos, i);
			if (!*path)
				string_conc(path, cmd);
			else
			{
				string_conc(path, "/");
				string_conc(path, cmd);
			}
			if (cmd_cln(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
