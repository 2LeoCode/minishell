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

void	numeric_argument_required(const char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
	minishell_exit(255);
}

int	builtin_exit(int argc, char **argv, char **envp)
{
	long long			ret;
	unsigned long long	value;
	char				*ptr;

	(void)envp;
	ret = 0;
	write(1, "exit\n", 5);
	if (argc > 2)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		return (1);
	}
	if (argc == 2)
	{
		ptr = *++argv;
		value = ft_atoll_u(ptr + (*ptr == '-'));
		if (ft_wrdlen(ptr + (*ptr == '-')) > 20 || value > LLONG_MAX)
			numeric_argument_required(*argv);
		ret = ft_atoll(ptr);
	}
	minishell_exit((unsigned char)ret);
	return (0);
}
