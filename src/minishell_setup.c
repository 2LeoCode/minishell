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

static int	setup_termios(struct termios * current, struct termios * backup)
{
	if ((tcgetattr(0, current) == -1)
	|| (tcgetattr(0, backup) == -1))
		return (-1);
	current->c_lflag &= ~(ICANON);
	current->c_lflag &= ~(ECHO);
	if (tcsetattr(0, 0, current) == -1)
	{
		write(2, "Error while setting terminal in non-cannonical mode\n", 52);
		return (-1);
	}
	return (0);
}

static int	setup_termcaps(t_term * tc)
{
	int			ret;
	char *		term_name;

	if (!(term_name = ft_getenv("TERM")))
		write(2, "Specify a terminal type with 'TERM=<type>'.\n", 44);
	else if (!(ret = tgetent(NULL, term_name)))
		write(2, "Your terminal is not defined in termcap database (or too little information).\n", 78);
	else if (ret == -1)
		write(2, "Could not access the termcap database.\n", 39);
	if (!term_name || (ret != 1))
		return (-1);
	tc->le = tgetstr("le", NULL);
	tc->ri = tgetstr("nd", NULL);
	tc->ks = "\033[0K";
	tc->ile = tgetstr("LE", NULL);
	return (0);
}

void		minishell_init(t_shell *ms, const char *executable_name)
{
	ms->executable_name = (char *)executable_name;
	ms->history_path = NULL;
	ms->history = NULL;
	env = NULL;
	ms->cmd_list[0] = "cd";
	ms->cmd_list[1] = "echo";
	ms->cmd_list[2] = "env";
	ms->cmd_list[3] = "exit";
	ms->cmd_list[4] = "export";
	ms->cmd_list[5] = "pwd";
	ms->cmd_list[6] = "unset";
	ms->builtin_fct_list[0] = &builtin_cd;
	ms->builtin_fct_list[1] = &builtin_echo;
	ms->builtin_fct_list[2] = &builtin_env;
	ms->builtin_fct_list[3] = &builtin_exit;
	ms->builtin_fct_list[4] = &builtin_export;
	ms->builtin_fct_list[5] = &builtin_pwd;
	ms->builtin_fct_list[6] = &builtin_unset;
}

int				minishell_setup(t_shell *ms, char **envp)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	ms->history = lst_new();
	if (!ms->history)
		return (-1);
	while (envp[count])
		count++;
	env = malloc(sizeof(struct s_env) + count);
	if (!env)
		return (-1);
	env->count = count;
	ft_addenv("HISTFILE", ".ms_history");
	while (++i < count)
		env->data[i] = envp[i];
	if (get_history(ms) || setup_termcaps(&ms->tcaps)
	|| setup_termios(&ms->term_shell, &ms->term_backup))
		return (-1);
	return (0);
}
