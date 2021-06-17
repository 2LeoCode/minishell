/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_process_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 17:40:58 by lsuardi           #+#    #+#             */
/*   Updated: 2021/04/01 17:45:54 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	process_hist(int key, t_input *input)
{
	if (key == _KEY_UP)
	{
		input->hist = input->hist->next;
		input->in = ft_strdup(input->hist->data);
	}
	else if (key == _KEY_DOWN)
	{
		input->hist = input->hist->prev;
		input->in = ft_strdup(input->hist->data);
	}
	if (!input->in)
		return (-1);
	input->prev_index = input->index;
	input->index = ft_strlen(input->in);
	return (0);
}

void	handle_sigint(t_input *input)
{
	g_global_data.sigint = false;
	reset_input(input, NULL);
}

/*
**	This function is used only when we are at the beginning of the history and
**	we press the DOWN key: it will set the input to an empty string and reset
**	the current index to 0. (It may be useful for CTRL-C too, but I didn't
**	implemented it yet).
*/
int	reset_input(t_input *input, const t_list *history)
{
	free(input->in);
	input->in = ft_strdup("");
	if (!input->in)
		return (-1);
	if (history)
		input->hist = (t_list *)history;
	input->prev_index = input->index;
	input->index = 0;
	return (0);
}

/*
**	The function called when we reach the end of the history, it will simply
**	make a beep sound (this function is just for space economy).
*/
int	key_hist_block(void)
{
	ft_beep();
	return (1);
}

/*
**	This function will be called at the end of the `key_process` function
**	everytime the input is modified, it will erase the old input, write the
**	new input, then put the cursor back where it was.
*/
int	update_input(const t_term *tcaps, t_input *input)
{
	if (input->prev_index)
		tputs(tparm(tcaps->ile, input->prev_index), 1, ft_putchar);
	tputs(tcaps->ks, 1, ft_putchar);
	ft_putstr(input->in);
	input->prev_len = ft_strlen(input->in);
	if (input->prev_len != input->index)
		tputs(tparm(tcaps->ile, input->prev_len - input->index), 1, ft_putchar);
	return (0);
}
