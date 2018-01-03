/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 19:53:53 by vlvereta          #+#    #+#             */
/*   Updated: 2017/11/22 19:57:59 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_next_line(const int fd, char **line)
{
	t_list			*node;
	static t_list	*head;

	if (fd < 0 || !line || BUFF_SIZE < 1)
		return (-1);
	*line = NULL;
	if (!(node = find_fd(&head, fd)))
		return (-1);
	if (!node->i && !node->r)
		return (node_delete(&head, node));
	return (write_line(line, node) == -1 ? -1 : 1);
}

t_list	*find_fd(t_list **head, int fd)
{
	int		temp_r;
	t_list	*new;
	t_list	*temp;

	if (head && (temp = *head) && *head)
		while (temp->next && (temp = temp->next))
			if ((temp->prev)->fd == fd)
				return (temp->prev);
	if (head && *head && temp->fd == fd)
		return (temp);
	if (!(new = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	new->fd = fd;
	new->i = 0;
	new->next = NULL;
	new->prev = temp;
	new->r = read(fd, new->buf, BUFF_SIZE);
	temp_r = new->r;
	temp_r == -1 ? (free(new)) : ((new->buf)[new->r] = '\0');
	temp_r == -1 ? (new = NULL) : 0;
	if (!temp)
		*head = new;
	else
		temp->next = new;
	return (new);
}

int		write_line(char **line, t_list *node)
{
	int	j;
	int	over_read;

	j = node->i;
	over_read = (!node->r ? 1 : 0);
	while ((node->buf)[j] && (node->buf)[j] != '\n')
		j++;
	if ((j = spacing(line, j)) == -1)
		return (-1);
	while ((node->buf)[node->i] && (node->buf)[node->i] != '\n')
		(*line)[j++] = (node->buf)[(node->i)++];
	(*line)[j] = '\0';
	if ((node->buf)[node->i] == '\n')
	{
		over_read = 1;
		(node->i)++;
	}
	if (!((node->buf)[node->i]))
	{
		if ((node->r = read(node->fd, node->buf, BUFF_SIZE)) == -1)
			return (-1);
		(node->buf)[node->r] = '\0';
		node->i = 0;
	}
	return (over_read ? 1 : write_line(line, node));
}

int		spacing(char **line, int ex_space)
{
	int		i;
	char	*temp;

	if (*line)
	{
		i = 0;
		while ((*line)[i])
			i++;
		if ((temp = (char *)malloc(sizeof(char) * (i + ex_space + 1))))
		{
			i = 0;
			while ((*line)[i])
			{
				temp[i] = (*line)[i];
				i++;
			}
			free(*line);
			*line = temp;
			return (i);
		}
	}
	else if ((*line = (char *)malloc(sizeof(char) * (ex_space + 1))))
		return (0);
	return (-1);
}

int		node_delete(t_list **head, t_list *node)
{
	if (head && *head && node)
	{
		if (node->prev)
			(node->prev)->next = node->next;
		else
			*head = node->next;
		if (node->next)
			(node->next)->prev = node->prev;
		free(node);
		node = NULL;
	}
	return (0);
}

