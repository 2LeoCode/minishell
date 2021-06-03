/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 20:38:22 by lsuardi           #+#    #+#             */
/*   Updated: 2021/04/03 18:22:37 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int		process_key(t_shell *ms, t_input *input, int key)
{
	int ret;

	if (key == -1)
		return (-1);
	if (key == _KEY_ENTER)
		return (1);
	if (ft_isprint(key) && process_key_print(input, key))
		return (-1);
	else if (key == _KEY_DELETE)
	{
		if (!input->index)
			return (0);
		if (process_key_del(input))
			return (-1);
	}
	else if (key == _KEY_LEFT)
		return (process_key_left(&ms->tcaps, input));
	else if (key == _KEY_RIGHT)
		return (process_key_right(&ms->tcaps, input));
	else if (((key == _KEY_UP) || (key == _KEY_DOWN))
	&& !!(ret = process_key_hist(ms->history, input, key)))
		return (-1 * (ret == -1));
	return (update_input(&ms->tcaps, input));
}

static int		get_input(t_shell * ms, char ** final_input)
{
	int			key;
	t_input		input;
	int			ret;

	if (!(input.in = ft_strdup("")))
		return (-1);
	input.index = 0;
	input.prev_index = 0;
	input.hist = ms->history;
	input.prev_hist = NULL;
	key = 0;
	input.prev_len = 0;
	while (!(ret = process_key(ms, &input, ft_getchar())))
		continue ;
	if (ret == -1)
		free(input.in);
	else
	{
		write(1, "\n", 1);
		*final_input = input.in;
	}
	return (ret);
}

static int		execute_cmd(t_shell *ms, char *input)
{
	//t_list		*cmds;
	//int			builtin_index;
	//pid_t		cpid;

	if (/*lst_init(&cmds)
	|| */*input && ((!ms->history || ft_strcmp(input, (char*)ms->history->data))
	&& lst_push_front(ms->history, input, ft_strlen(input)))
	/*|| parse_cmds(&cmds, input)*/)
		return (-1);
	/*it = cmds->next;
	while (++it != cmds)
	{
	}*/
	printf("Hello World\n");
	return (0);
}

static sig_t	setup_signal(void)
{
	sig_t	ret;

	ret = signal(SIGINT, &int_handler);
	if (ret != SIG_ERR)
		ret = signal(SIGABRT, &abort_handler);
	return (ret);
}

int 			main(int argc, char **argv, char **envp)
{
	//char		*input;
	int			read_ret;
	t_shell		ms;

	(void)argc;
	if (gb_add(&ms, minishell_clear))
		return (-1);
	minishell_init(&ms, argv[0]);
	if ((setup_signal() == SIG_ERR)
	|| minishell_setup(&ms, envp))
		return (minishell_error());
	read_ret = 1;
	/*while (1)
	{
		write(1, "minishell-1.0$ ", 15);
		if (((read_ret = get_input(&ms, &input)) == -1)
		|| (read_ret && ((execute_cmd(&ms, input) == -1))))
			return (minishell_error());
	}*/
	gb_clear();
	save_history(&ms);
	return (0);
}
