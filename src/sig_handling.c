/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 21:19:57 by lsuardi           #+#    #+#             */
/*   Updated: 2021/03/01 22:38:50 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void int_handler(int sig)
{
	(void)sig;
	write(1, "\r\033[2Kminishell-1.0# \nminishell-1.0# ", 36);
	errno = 130;
}
