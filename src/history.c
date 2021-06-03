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
int		get_history(t_shell *ms)
{
	char	*line;
	int		fd;
	int		ret;
	int		i;

	ms->history_path = ft_getenv("HISTFILE");
	if ((fd = open(ms->history_path, O_RDONLY)) == -1)
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
					&& lst_push_front(ms->history, &line[i],
					ft_strlen(&line[i])))
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
int		save_history(t_shell *ms)
{
	int			fd;
	t_list		*lst;

	if ((fd = open(ms->history_path, O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR))
				== -1)
		return (-1);
	lst = ms->history->prev;
	while (lst != ms->history)
	{
		write(fd, ": :0;", 5);
		ft_putendl_fd((char*)lst->data, fd);
		lst = lst->prev;
	}
	return (0);
}
