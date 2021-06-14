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

bool	ft_strisnumber(const char *s)
{
	while (ft_isspace(*s))
		s++;
	if (*s == '-' || *s == '+')
		s++;
	while (ft_isdigit(*s))
		s++;
	while (ft_isspace(*s))
		s++;
	return (!*s);
}

int builtin_exit(int ac, char **av, char **ep)
{
	long long	ret;

	(void)ep;
	ret = 0;
	write(1, "exit\n", 5);
	if (ac > 2)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		return (1);
	}
	if (ac == 2 && 	**++av == '-')
		(*av)++;
	if (ac == 2 && (!ft_strisnumber(*av)
				|| ft_wrdlen(*av) > 19
				|| (ft_wrdlen(*av) == 19
				&& ft_strcmp(*av, "9223372036854775807") > 0)))
	{
		write(2, "minishell: exit: ", 17);
		ft_putstr_fd(*av, 2);
		write(2, ": numeric argument required\n", 28);
		minishell_exit(255);
	}
	minishell_exit((unsigned char)ret);
	return (0);
}
