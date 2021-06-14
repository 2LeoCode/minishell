/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 22:24:19 by lsuardi           #+#    #+#             */
/*   Updated: 2021/03/29 17:20:56 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
**	This function will read the history file that we set earlier in the
**	HISTFILE environment variable using successive `get_next_line` calls to
**	store the command history inside our chained list.
*/
int		get_history(void)
{
	char	*line;
	int		fd;
	int		ret;
	int		i;

	if ((fd = open(g_global_data.history_path, O_RDONLY)) == -1)
		return (-1 * (errno != ENOENT));
	ret = 1;
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
			return (-1);
		i = 0;
		while (line[i] && (line[i++] != ';'))
			continue ;
		if (i && (line[i - 1] == ';')
					&& lst_push_front(g_global_data.history, &line[i],
					ft_strlen(&line[i]) + 1))
			ret = -1;
		free(line);
	}
	line = NULL;
	return (ret);
}

/*
**	This will simply do the opposite: read the command history from our list,
**	and write it back into our history file.
*/
int		save_history(void)
{
	int			fd;
	t_list		*lst;

	fd = open(g_global_data.history_path, O_CREAT | O_TRUNC | O_WRONLY, S_IWUSR | S_IRUSR);
	if (fd == -1)
		return (-1);
	lst = g_global_data.history->prev;
	while (lst != g_global_data.history)
	{
		write(fd, ": :0;", 5);
		ft_putendl_fd((char *)lst->data, fd);
		lst = lst->prev;
	}
	close(fd);
	return (0);
}
