/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 15:45:43 by lsuardi           #+#    #+#             */
/*   Updated: 2021/03/01 22:34:46 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_next_line.h>

static size_t	get_line_len(t_list *tmp)
{
	size_t	len;
	int		i;
	char	*cur_pos;

	len = 0;
	cur_pos = (tmp ? tmp->pos : NULL);
	while (tmp && cur_pos && *cur_pos && (*(cur_pos++) - '\n'))
		len++;
	if (cur_pos && !*cur_pos)
		while (tmp && tmp->next)
		{
			i = 0;
			tmp = tmp->next;
			while (tmp->buf[i] && (tmp->buf[i++] - '\n'))
				len++;
			if (tmp->buf[i])
				return (len);
		}
	return (len);
}

static int		lst_fill_line(char **line, t_list **lst)
{
	int		i;

	i = 0;
	while (*lst && (*lst)->next)
	{
		i = 0;
		(*lst)->pos = NULL;
		*lst = (*lst)->next;
		while ((*lst)->buf[i] && ((*lst)->buf[i] - '\n'))
			*((*line)++) = (*lst)->buf[i++];
		if ((*lst)->buf[i])
			break ;
	}
	return (i);
}

static int		lst_get_line(char **line, t_buffer *buf)
{
	t_list	*tmp;
	size_t	len;
	int		c;
	int		ret;

	tmp = buf->cur;
	len = get_line_len(tmp);
	if (!(*line = (char*)malloc(sizeof(char) * (len + 1))))
		return (clear_buffer(buf) - 1);
	while (tmp && *tmp->pos && (*tmp->pos - '\n'))
		*((*line)++) = *(tmp->pos++);
	ret = 0;
	if (tmp && !(c = *tmp->pos))
		ret = lst_fill_line(line, &tmp);
	**line = 0;
	*line -= len;
	if (!tmp || (tmp && !c && (tmp->pos || !tmp->buf[ret])))
		return (clear_buffer(buf));
	buf->cur = tmp;
	tmp->pos = (c ? (tmp->pos + 1) : &tmp->buf[ret + 1]);
	if (!buf->id)
		clear_buffer(buf);
	return (1);
}

static int		lst_read_line(int fd, t_buffer *buf)
{
	if (!buf->init)
	{
		if (!(buf->all = malloc(sizeof(t_list))))
			return (clear_buffer(buf) - 1);
		buf->all->next = NULL;
		if ((buf->read_ret = read(fd, buf->all->buf, BUFFER_SIZE)) < 0)
			return (clear_buffer(buf) - 1);
		buf->all->buf[buf->read_ret] = 0;
		buf->all->pos = buf->all->buf;
		buf->last = buf->all;
		buf->cur = buf->all;
		buf->init = 1;
	}
	while ((buf->read_ret == BUFFER_SIZE) && !lst_chr(buf->cur, '\n'))
	{
		if (!(buf->last->next = malloc(sizeof(t_list))))
			return (clear_buffer(buf) - 1);
		buf->last = buf->last->next;
		buf->last->pos = NULL;
		buf->last->next = NULL;
		if ((buf->read_ret = read(fd, buf->last->buf, BUFFER_SIZE)) < 0)
			return (clear_buffer(buf) - 1);
		buf->last->buf[buf->read_ret] = 0;
	}
	return ((buf->read_ret < BUFFER_SIZE) ? 0 : 1);
}

int				get_next_line(int fd, char **line)
{
	static t_buffer		buf[MAX_FD];
	int					ret;
	t_list				*tmp;

	if (BUFFER_SIZE < 1 || fd < 0 || !line)
		return (-1);
	buf[fd].id = fd;
	if (!buf[fd].init)
	{
		if ((lst_read_line(fd, &buf[fd]) < 0)
		|| ((ret = lst_get_line(line, &buf[fd])) < 0))
			return (-1);
		return (ret);
	}
	while (buf[fd].all && (buf[fd].all != buf[fd].cur))
	{
		tmp = buf[fd].all;
		buf[fd].all = buf[fd].all->next;
		free(tmp);
	}
	if ((!lst_chr(buf[fd].cur, '\n') && (lst_read_line(fd, &buf[fd]) < 0))
	|| ((ret = lst_get_line(line, &buf[fd])) < 0))
		return (-1);
	return (ret);
}
