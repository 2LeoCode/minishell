/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 21:19:57 by lsuardi           #+#    #+#             */
/*   Updated: 2021/03/31 21:21:03 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	quit_handler(int sig)
{
	(void)sig;
	errno = 0;
	if (g_global_data.current_cpid)
	{
		kill(g_global_data.current_cpid, SIGQUIT);
		g_global_data.current_cpid = 0;
		ft_putendl_fd("Quit: 3", 2);
		errno = 131;
	}
	g_global_data.status = errno;
}

/*
**	When a SIGINT is received (for example through CTRL+C), it will not exit the
**	program, it will instead insert a new line and write the shell prompt.
*/
void	int_handler(int sig)
{
	(void)sig;
	g_global_data.sigint = true;
	if (g_global_data.current_cpid)
	{
		kill(g_global_data.current_cpid, SIGINT);
		g_global_data.current_cpid = 0;
		write(1, "\n", 1);
		errno = 130;
	}
	else
	{
		write(1, "\nminishell-1.0$ ", 16);
		errno = 1;
	}
	g_global_data.status = errno;
}
