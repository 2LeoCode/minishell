/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 23:55:46 by lsuardi           #+#    #+#             */
/*   Updated: 2021/03/28 23:55:51 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_get_current_dir_name(void)
{
	char	*buf;
	char	*cwd;
	size_t	size;

	size = 1;
	cwd = NULL;
	while (!cwd)
	{
		buf = (char *)ft_calloc(size + 1, sizeof(char));
		if (!buf)
			return (NULL);
		cwd = getcwd(buf, size);
		if (!cwd)
		{
			free(buf);
			if (errno == ERANGE)
				size *= 2;
			else
				return (NULL);
		}
	}
	return (buf);
}

int builtin_pwd(int ac, char **av, char **ep)
{
	char	*cwd;

	(void)ac;
	(void)av;
	(void)ep;
	cwd = ft_get_current_dir_name();
	if (!cwd)
		return (-1);
	ft_putendl(cwd);
	free(cwd);
	return (0);
}
