/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 19:35:54 by lsuardi           #+#    #+#             */
/*   Updated: 2021/04/03 15:02:17 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		no_such_file(const char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	perror(path);
	return (-1);
}

int		builtin_cd(int ac, char **av, char **ep)
{
	char	*home;

	(void)ep;
	if (ac == 1 || !ft_strcmp(av[1], "~"))
	{
		home = ft_getenv("HOME");
		if (!home)
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			return (1);
		}
		if (chdir(home))
			return (no_such_file(home));
	}
	else if (chdir(av[1]))
	{
		perror("minishell");
		return (1);
	}
	if (ft_setenv("PWD", getenv("PWD")))
		return (-1); // Je recupere la vraie variable PWD dans la globale
	return (0);
}
