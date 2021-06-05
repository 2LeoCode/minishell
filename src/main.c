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

/*
**	In that function we have our data structures and the last key that has been
**	pressed. So we will check for every "action" keys (ENTER, arrow keys, and
**	DEL key), or if the key is a printable character that we can display, and
**	then we call different function and return different values:
**	If the key value is -1, it will mean that an error occurred in our
**	`ft_getchar` function (so `read` returned -1), or if an allocation failed,
**	we will return -1, else we will return 1 only if `key` is ENTER to inform
**	that the command has been sent to the program, otherwise we will return 0.
*/
static int		process_key(t_shell *ms, t_input *input, int key)
{
	int ret;

	if (g_global_data.sigint)
	{
		g_global_data.sigint = false;
		reset_input(input, NULL);
	}
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

/*
**	The function to handle input in non-canonical mode (to be able to move the
**	cursor and to have a command history):
**	We have our input struct that we setup with default values (the cursor index
**	is 0 at the beginning as well as the history pointer initially points to the
**	last command in history), we then call our `process_key` function (see
**	above), we send it our main struct ms, the address of our input struct to be
**	able to edit it, and the key which is pressed through a custom `ft_getchar`
**	function that handles non ascii keys that wee need such as ENTER, LEFT, ...
**	(see libft for `ft_getchar`). `process_key` will return 1 when the ENTER key
**	is pressed, otherwise it will return 0, so we loop on that function until it
**	returns a non null value to process every key one by one.
**	Then we check if the return value is -1, which means that an error occured,
**	in that case we will just free the input string (`input.in`), else we write
**	a new line and we put the input in `*final_input` string.
**	We then return `ret` which is the last return value of `process_key` (-1 on
**	failure or 1 on success)
*/
static int		get_input(t_shell *ms, char **final_input)
{
	t_input		input;
	int			ret;

	if (!(input.in = ft_strdup("")))
		return (-1);
	input.index = 0;
	input.prev_index = 0;
	input.hist = ms->history;
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

/*
**	The parse-and-execute part: we send an input to this function through a
**	string, then we add this input to the command history, then we parse and
**	execute the command.
*/
static int		process_input(t_shell *ms, char *input)
{
	if (*input && ((!lst_size(ms->history)
				|| ft_strcmp(input, (char*)ms->history->next->data))
				&& lst_push_front(ms->history, input, ft_strlen(input) + 1)))
		return (-1);
	return (0);
}

/*
**	We attach our handler functions to different signals
*/
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
	char		*input;
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
	while (1)
	{
		write(1, "minishell-1.0$ ", 15);
		if (((read_ret = get_input(&ms, &input)) == -1)
		|| (read_ret && ((process_input(&ms, input) == -1))))
			return (minishell_error());
	}
	gb_load();
	gb_clear();
	save_history(&ms);
	tcsetattr(0, 0, &ms.term_backup);
	return (0);
}
