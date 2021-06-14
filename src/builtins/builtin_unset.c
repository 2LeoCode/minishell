/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 23:55:53 by lsuardi           #+#    #+#             */
/*   Updated: 2021/03/29 00:30:27 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int builtin_unset(int ac, char **av, char **ep)
{
	(void)ep;
	while (--ac > 0)
	{
		if (!ft_strcmp(av[ac], "PATH"))
		{
			ft_destroy_array((void **)g_global_data.path, NULL_ENDED);
			g_global_data.path = NULL;
		}
		if (ft_delenv(av[ac]))
			return (-1);
	}
	return (0);
}
