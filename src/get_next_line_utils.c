/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 21:59:27 by lsuardi           #+#    #+#             */
/*   Updated: 2020/06/11 15:12:56 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_next_line.h>

void	*lst_chr(t_list *lst, int c)
{
	int		i;
	char	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst->pos;
	while (*tmp && (*tmp - c))
		tmp++;
	if (*tmp == c)
		return (tmp);
	while (lst && lst->next)
	{
		i = 0;
		lst = lst->next;
		while (lst->buf[i] && (lst->buf[i] - c))
			i++;
		if (lst->buf[i])
			return ((void*)&lst->buf[i]);
	}
	return (NULL);
}

int		clear_buffer(t_buffer *buf)
{
	t_list	*tmp;

	while (buf->all)
	{
		tmp = buf->all;
		buf->all = buf->all->next;
		free(tmp);
		tmp = NULL;
	}
	buf->cur = NULL;
	buf->last = NULL;
	buf->init = 0;
	return (0);
}
