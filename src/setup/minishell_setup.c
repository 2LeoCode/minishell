/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_setup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 00:19:08 by lsuardi           #+#    #+#             */
/*   Updated: 2021/03/31 23:29:24 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

struct s_globaldata	g_global_data = {0};

/*
**	Here we will initialize all constant variables and set our pointers to NULL
**	before doing anything that could fail.
*/
void	minishell_init(t_shell *ms, const char *executable_name)
{
	ms->executable_name = (char *)executable_name;
	g_global_data.history_path = NULL;
	g_global_data.history = NULL;
	ms->builtin_fct_name[0] = "cd";
	ms->builtin_fct_name[1] = "echo";
	ms->builtin_fct_name[2] = "env";
	ms->builtin_fct_name[3] = "exit";
	ms->builtin_fct_name[4] = "export";
	ms->builtin_fct_name[5] = "pwd";
	ms->builtin_fct_name[6] = "unset";
	ms->builtin_fct_ptr[0] = &builtin_cd;
	ms->builtin_fct_ptr[1] = &builtin_echo;
	ms->builtin_fct_ptr[2] = &builtin_env;
	ms->builtin_fct_ptr[3] = &builtin_exit;
	ms->builtin_fct_ptr[4] = &builtin_export;
	ms->builtin_fct_ptr[5] = &builtin_pwd;
	ms->builtin_fct_ptr[6] = &builtin_unset;
}

/*
**	We attach our handler functions to different signals
*/
sig_t	setup_signal(void)
{
	sig_t	ret;

	ret = signal(SIGINT, &int_handler);
	if (ret != SIG_ERR)
		ret = signal(SIGQUIT, &quit_handler);
	return (ret);
}

/*
**	Here we initialize all our data that needs allocation or that can fail to
**	initialize, so global environment variables, the list containing the
**	command history, the termcap library and the termios structures that will
**	allow us to change the terminal attributes (see `setup_termios` above)
*/
int	setup_env(char **envp, int cnt)
{
	int	i;

	if (alloc_env(&g_global_data.env, (cnt + 1) * sizeof(char *)))
		return (-1);
	g_global_data.env->data[cnt] = NULL;
	g_global_data.env->count = cnt;
	i = -1;
	while (++i < g_global_data.env->count)
	{
		g_global_data.env->data[i] = ft_strdup(envp[i]);
		if (!g_global_data.env->data[i])
		{
			ft_clearenv();
			g_global_data.env = NULL;
			return (-1);
		}
	}
	g_global_data.path = ft_split(ft_getenv("PATH"), ':');
	if (!g_global_data.path)
	{
		ft_clearenv();
		return (-1);
	}
	return (0);
}

int	minishell_setup(t_shell *ms, char **envp)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	g_global_data.history = lst_new();
	if (!g_global_data.history)
		return (-1);
	while (envp[count])
		count++;
	if (setup_env(envp, count))
		return (-1);
	g_global_data.status = 0;
	g_global_data.history_path = ft_getenv("HISTFILE");
	if (!g_global_data.history_path)
		g_global_data.history_path = ".ms_history";
	if (get_history() || setup_termcaps(&ms->tcaps) || setup_termios())
		return (-1);
	return (0);
}
