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

/*
**	When a SIGINT is received (for example through CTRL+C), it will not exit the
**	program, it will instead insert a new line and write the shell prompt.
*/
void int_handler(int sig)
{
	(void)sig;
	write(1, "\nminishell-1.0$ ", 16);
	g_global_data.sigint = true;
	errno = 130;
}

/*
**	A default abort-handler that will free the memory stored in our garbage
**	(see garbage.h) before exiting. That may be useful if we want to send a
**	SIGABRT if something goes wrong.
*/
void abort_handler(int sig)
{
	(void)sig;
	gb_load();
	gb_clear();
	exit(errno);
}
