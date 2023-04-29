#include "shell.h"

/**
 * input_buf - buffers
 * @info: param structure
 * @buf: addr of buffer
 * @len: addr of length var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{

		free(*buf);
		*buf = NULL;
		signal(SIGINT, ctrl_Handle);
#if USEgt_line
		r = getline(buf, &len_p, stdin);
#else
		r = gt_line(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			info->totalLns_cnt_flag = 1;
			deleteComments(*buf);
			make_list_of_history(info, *buf, info->histcount++);

			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * gt_inpuutt - minus
 * @info: para struct
 *
 * Return: bytes read
 */
ssize_t gt_inpuutt(info_t *info)
{
	static char *buf;
	static size_t i, x, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		x = i;
		p = buf + i;

		_checker(info, buf, &x, i, len);
		while (x < len)
		{
			if (equal_to_chain(info, buf, &x))
				break;
			x++;
		}

		i = x + 1;
		if (i >= len)
		{
			i = len = 0;
			info->command_typ_buffer = CMD_NORM;
		}

		*buf_p = p;
		return (string__length(p));
	}

	*buf_p = buf;
	return (r);
}

/**
 * read_buf - reads
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * gt_line - input from STDIN
 * @info: 
 * @ptr: preallocated or NULL
 * @length:  ptr buffer if not NULL
 *
 * Return: s
 */
int gt_line(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = chars_str(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) 
		return (p ? free(p), -1 : -1);

	if (s)
		conc_str(new_p, buf + i, k - i);
	else
		copy_str(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * ctrl_Handle - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void ctrl_Handle(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
