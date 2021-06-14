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

void	static_clear(t_cmd **cmd_arr, char **tokens)
{
	static t_cmd	**arr = NULL;
	static void		**tok = NULL;

	if (cmd_arr || tokens)
	{
		arr = cmd_arr;
		tok = (void **)tokens;
	}
	else
	{
		if (arr)
			destroy_cmd_array(arr);
		if (tok)
			ft_destroy_array(tok, NULL_ENDED);
	}
}

void	pre_exit_save(t_cmd **cmd_arr, char **tokens)
{
	static_clear(cmd_arr, tokens);
}

void	pre_exit_clear(void)
{
	static_clear(NULL, NULL);
}

/*
**	Destroys all global data
*/
void	minishell_clear(void)
{
	lst_destroy(g_global_data.history);
	ft_destroy_array((void **)g_global_data.path, NULL_ENDED);
	ft_clearenv();
}
