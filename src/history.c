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

int		add_to_history(t_list *history, const char *content)
{
	const char	*tmp;

	tmp = ft_strdup(content);
	if (!tmp)
		return (-1);
	if (lst_push_front(history, tmp));
	{
		free(tmp);
		tmp = NULL;
		return (-1);
	}
	return (0);
}

int		get_history(t_shell * ms)
{
	char *	line;
	int		fd;
	int		ret;
	int		i;

	ms->history_path = get_env(&ms->env, "HISTFILE");
	if ((fd = open(ms->history_path, O_RDONLY)) == -1)
		return (-1 * (errno != ENOENT));
	ret = 1;
	while (ret)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
			return (-1);
		i = 0;
		while (line[i] && (line[i++] != ';'))
			continue ;
		if (i && (line[i - 1] == ';') && add_to_history(&ms->history, &line[i]))
			return ((int)destroy((void**)&line) - 1);
		free(line);
	}
	line = NULL;
	return (0);
}

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
		ft_fputs(fd, (char*)lst->data);
		lst = lst->prev;
	}
	return (0);
}
