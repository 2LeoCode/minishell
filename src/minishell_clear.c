/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_clear.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 21:15:49 by lsuardi           #+#    #+#             */
/*   Updated: 2021/04/01 16:15:43 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	minishell_clear(void *data)
{
	t_shell	*ms;

	ms = (t_shell *)data;
	lst_destroy(ms->history);
}
