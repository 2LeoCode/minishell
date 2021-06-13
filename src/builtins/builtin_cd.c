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

int		builtin_cd(int ac, char **av, char **ep)
{
	(void)ep;
	if (ac == 1 || strcmp(av[1], "~") != 0)
		chdir(ft_getenv("HOME"));
	else if (chdir(av[1]))
	{
		printf("%s : not a valid directory\n", av[1]);
		return (-1);
	}
	if (ft_setenv("PWD", getenv("PWD")))
		return (-1); // Je recupere la vraie variable PWD dans la globale
	return (0);
}
