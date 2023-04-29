#include "shell.h"

/**
 * retr_history_doc - gets hist
 * @info: para
 *
 * Return: allocs str containg istory
 */

char *retr_history_doc(info_t *info)
{
	char *buf, *dir;

	dir = gt_environ(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (string__length(dir) + string__length(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	copy_string(buf, dir);
	string_conc(buf, "/");
	string_conc(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - create or append
 * @info: the parameter struct
 *
 * Return: 1 , else -1
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = retr_history_doc(info);
	list_t *data = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (data = info->history; data; data = data->next)
	{
		_putsfd(data->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - reads hist from file
 * @info: the parameter struct
 *
 * Return: history coiunts on success, 0 otherwise
 */
int read_history(info_t *info)
{
	int i, last = 0, totalLns_cnt = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = retr_history_doc(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			make_list_of_history(info, buf + last, totalLns_cnt++);
			last = i + 1;
		}
	if (last != i)
		make_list_of_history(info, buf + last, totalLns_cnt++);
	free(buf);
	info->histcount = totalLns_cnt;
	while (info->histcount-- >= HIST_MAX)
		remove_data(&(info->history), 0);
	reshuffle_hist(info);
	return (info->histcount);
}

/**
 * make_list_of_history - adds entry hist
 * @info: structure
 * @buf: buffer
 * @totalLns_cnt: the history
 *
 * Return: Always 0
 */
int make_list_of_history(info_t *info, char *buf, int totalLns_cnt)
{
	list_t *data = NULL;

	if (info->history)
		data = info->history;
	add_poss_end(&data, buf, totalLns_cnt);

	if (!info->history)
		info->history = data;
	return (0);
}

/**
 * reshuffle_hist - rreshuffle
 * @info: Structure
 *
 * Return: the new histcount
 */
int reshuffle_hist(info_t *info)
{
	list_t *data = info->history;
	int i = 0;

	while (data)
	{
		data->num = i++;
		data = data->next;
	}
	return (info->histcount = i);
}
