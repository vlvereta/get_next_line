/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 19:54:08 by vlvereta          #+#    #+#             */
/*   Updated: 2017/11/22 19:56:57 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 32

# include <unistd.h>
# include <stdlib.h>

typedef struct      s_fdlst
{
	int             fd;
	char            buf[BUFF_SIZE + 1];
	int             i;
	int             r;
	struct s_fdlst  *prev;
	struct s_fdlst  *next;
}                   t_fdlst;

int                 get_next_line(const int fd, char **line);
t_list              *find_fd(t_fdlst **head, int fd);
int                 write_line(char **line, t_fdlst *node);
int                 spacing(char **line, int ex_space);
int                 node_delete(t_fdlst **head, t_fdlst *node);

#endif
