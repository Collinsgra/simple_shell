#include "shell.h"

/**
 * add_data - adds
 * @head: ptr head
 * @str: str field of data
 * @num: data index used by history
 *
 * Return: size of list
 */
list_t *add_data(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	setMemory((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = string_duplicate(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_poss_end - adds a data to the end of the list
 * @head: ptr head
 * @str: str field
 * @num: used by history
 *
 * Return: size of list
 */
list_t *add_poss_end(list_t **head, const char *str, int num)
{
	list_t *new_data, *data;

	if (!head)
		return (NULL);

	data = *head;
	new_data = malloc(sizeof(list_t));
	if (!new_data)
		return (NULL);
	setMemory((void *)new_data, 0, sizeof(list_t));
	new_data->num = num;
	if (str)
	{
		new_data->str = string_duplicate(str);
		if (!new_data->str)
		{
			free(new_data);
			return (NULL);
		}
	}
	if (data)
	{
		while (data->next)
			data = data->next;
		data->next = new_data;
	}
	else
		*head = new_data;
	return (new_data);
}

/**
 * string_prt_st - prints the string only
 * @h: pointer to first data
 *
 * Return: size of list
 */
size_t string_prt_st(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * remove_data - deletes data
 * @head: addressptr
 * @index: index
 *
 * Return: 1 on success, 0 on failure
 */
int remove_data(list_t **head, unsigned int index)
{
	list_t *data, *last_data;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		data = *head;
		*head = (*head)->next;
		free(data->str);
		free(data);
		return (1);
	}
	data = *head;
	while (data)
	{
		if (i == index)
		{
			last_data->next = data->next;
			free(data->str);
			free(data);
			return (1);
		}
		i++;
		last_data = data;
		data = data->next;
	}
	return (0);
}

/**
 * free_list - frees datas
 * @head_ptr: address of pointer to head data
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *data, *next_data, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	data = head;
	while (data)
	{
		next_data = data->next;
		free(data->str);
		free(data);
		data = next_data;
	}
	*head_ptr = NULL;
}
