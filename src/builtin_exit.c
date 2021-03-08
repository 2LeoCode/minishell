/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 00:02:27 by lsuardi           #+#    #+#             */
/*   Updated: 2021/03/07 18:23:54 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int builtin_exit(int ac, char ** av, char ** ep)
{
	long long	ret;

	(void)ep;
	write(1, "exit\n", 5);
	if (ac < 2)
		minishell_clear(NULL);
	if (ac == 1)
		exit(0);
	else if (!str_isdigit(*av) || (ft_nblen(*av) > 19)
	|| (((ret = ft_atoll(*av)) < 0) && !ft_strchr(*av, '-')))
	{
		write(2, "minishell: exit: ", 6);
		ft_fputs(2, *av);
		write(2, ": numeric argument required\n", 28);
		minishell_clear(NULL);
		exit(255);
	}
	if (ac > 2)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		return (1);
	}
	exit((unsigned char)ret);
}
