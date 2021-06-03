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

/*
**	In this function we will get the current terminal attributes into two
**	`struct termios`, one that we edit through bit mask to remove the ICANON
**	(canonical-mode) and ECHO (echo-mode) and apply to our current terminal
**	through `tcsetattr`, and one that we will keep as a backup to reset the
**	terminal to how it was before at the end of the program.
**	The non-canonical mode will make the `read` function non-blocking, so every
**	key will be returned immediately without waiting for a new line like by
**	default.
**	And the echo mode just means that when you press a key it will echo it on
**	the terminal, so disabling it will just send the key to the program without
**	echoing it, so we will have to print it manually with `write`, this will
**	allow us to move our cursor and insert/delete characters in the middle of
**	our input.
*/
static int	setup_termios(struct termios *current, struct termios *backup)
{
	if ((tcgetattr(0, current) == -1)
	|| (tcgetattr(0, backup) == -1))
		return (-1);
	current->c_lflag &= ~(ICANON);
	current->c_lflag &= ~(ECHO);
	if (tcsetattr(0, 0, current) == -1)
	{
		write(2, "Error while editing terminal attributes\n", 40);
		return (-1);
	}
	return (0);
}

/*
**	Here we simply initialize the termcap library and pick up the termcaps that
**	we will need in the program into our `t_term` struct.
*/
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

/*
**	Here we will initialize all constant variables and set our pointers to NULL
**	before doing anything that could fail.
*/
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

/*
**	Here we initialize all our data that needs allocation or that can fail to
**	initialize, so global environment variables, the list containing the
**	command history, the termcap library and the termios structures that will
**	allow us to change the terminal attributes (see `setup_termios` above)
*/
int			minishell_setup(t_shell *ms, char **envp)
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
	env = malloc(sizeof(struct s_env) + count * sizeof(char *));
	if (!env)
		return (-1);
	env->count = count;
	while (++i < env->count)
	{
		env->data[i] = ft_strdup(envp[i]);
		if (!env->data[i])
		{
			while (i--)
				free(env->data[i]);
			free(env);
			return (-1);
		}
	}
	ft_addenv("HISTFILE", ".ms_history");
	i = -1;
	if (get_history(ms) || setup_termcaps(&ms->tcaps)
	|| setup_termios(&ms->term_shell, &ms->term_backup))
		return (-1);
	return (0);
}
