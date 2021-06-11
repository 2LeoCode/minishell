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

/*
**	Destroys all global data
*/
void	minishell_clear(void)
{
	for (t_list *it = g_global_data.history->next; it != g_global_data.history; it = it->next)
		printf("%s\n", it->data);
	lst_destroy(g_global_data.history);
	ft_clearenv();
}
