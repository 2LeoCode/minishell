/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 00:02:27 by lsuardi           #+#    #+#             */
/*   Updated: 2021/03/29 00:30:34 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
**	exit is not as tiny as we could think as there is a weird behavior in bash's
**	exit that trows an error when called with a value that is superior to
**	LONG_LONG_MAX (still needs some adjustments for lisibility)
*/
int builtin_exit(int ac, char ** av, char ** ep)
{
	long long	ret;
	char		*ng;

	(void)ep;
	write(1, "exit\n", 5);
	if (ac == 1)
		minishell_exit(0);
	else if (!ft_strisdigit(*av)
	|| (((ret = ft_atoll(*av)) < 0) && !(ng = ft_strchr(*av, '-')))
	|| ((ret > 0) && ng))
	{
		write(2, "minishell: exit: ", 6);
		ft_putstr_fd(*av, 2);
		write(2, ": numeric argument required\n", 28);
		minishell_exit(255);
	}
	if (ac > 2)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		return (1);
	}
	exit((unsigned char)ret);
}
