/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_setup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 00:19:08 by lsuardi           #+#    #+#             */
/*   Updated: 2021/03/04 21:04:01 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	minishell_clear(t_shell * ms)
{
	static t_shell * attached;

	if (!attached)
		attached = ms;
	else
	{
		varlist_clear(&attached->var.exp);
		varlist_clear(&attached->var.nexp);
		destroy((void**)&attached->output);
		attached = NULL;
	}
}

void	minishell_init(t_shell * ms, const char * executable_name)
{
	minishell_clear(ms);
	ms->var = NULL;
	ms->executable_name = executable_name;
	ms->pipe_output = NULL;
	ms->prev_input = NULL;
	ms->cmd_list = {
		"cd",
		"echo",
		"env",
		"exit",
		"export",
		"pwd",
		"unset"
	};
	ms->builtin_fct_list = {
		&builtin_cd,
		&builtin_echo,
		&builtin_env,
		&builtin_exit,
		&builtin_export,
		&builtin_pwd,
		&builtin_unset
	};
}

int		minishell_setup(t_shell * ms, const char ** envp)
{
	int		ret;
	char *	it;

	it = envp - 1;
	while (*(++it)))
		if (varlist_push_raw(&ms->var, *it, 1))
			return (-1);
	return (varlist_push(&ms->var, "?", "0", 0));
}
