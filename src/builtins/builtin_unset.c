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

int	builtin_unset(int argc, char **argv, char **envp)
{
	(void)envp;
	while (--argc > 0)
	{
		if (!ft_strcmp(argv[argc], "PATH"))
		{
			ft_destroy_array((void **)g_global_data.path, NULL_ENDED);
			g_global_data.path = NULL;
		}
		if (ft_delenv(argv[argc]))
			return (-1);
	}
	return (0);
}
