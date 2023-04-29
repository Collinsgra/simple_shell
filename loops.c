#include "shell.h"

/**
 * list_len - determne length
 * @h: ptr
 *
 * Return: size
 */
size_t list_len(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * stringList - return an array
 * @head: ptr of firts dara
 *
 * Return: array of strings
 */
char **stringList(list_t *head)
{
	list_t *data = head;
	size_t i = list_len(head), x;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; data; data = data->next, i++)
	{
		str = malloc(string__length(data->str) + 1);
		if (!str)
		{
			for (x = 0; x < i; x++)
				free(strs[x]);
			free(strs);
			return (NULL);
		}

		str = copy_string(str, data->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * listPrinted - print
 * @h: pointer to first data
 *
 * Return: size of list
 */
size_t listPrinted(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(changeNum(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * dt_begins_at - returns data
 * @data: ptr head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match data or null
 */
list_t *dt_begins_at(list_t *data, char *prefix, char c)
{
	char *p = NULL;

	while (data)
	{
		p = starts_with(data->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (data);
		data = data->next;
	}
	return (NULL);
}

/**
 * receiveData - ..
 * @head: ..
 * @data: ..
 *
 * Return: index of data or -1
 */
ssize_t receiveData(list_t *head, list_t *data)
{
	size_t i = 0;

	while (head)
	{
		if (head == data)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
