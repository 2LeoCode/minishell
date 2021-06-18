/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_process_0.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 17:39:51 by lsuardi           #+#    #+#             */
/*   Updated: 2021/04/01 17:40:27 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
**	Here we will process any printable key:
**	We will insert the character at the cursor position.
*/
int	process_key_print(t_input *input, int key)
{
	if (ft_strinsert(&input->in, input->index, key))
		return (-1);
	input->prev_index = input->index++;
	return (0);
}

/*
**	Here we will process the DEL key:
**	We will delete the character before the cursor position.
*/
int	process_key_del(t_input *input)
{
	input->prev_index = input->index--;
	if (ft_strerase(&input->in, input->index))
		return (-1);
	return (0);
}

/*
**	Here we will process the LEFT key:
**	We use the termcap 'le' to move the cursor a single case to the left,
**	but only if the cursor is not already at the beginning (otherwise it would
**	overlap in the shell prompt and eventually produce undefined behavior)
*/
int	process_key_left(const t_term *tcaps, t_input *input)
{
	if (input->index > 0)
	{
		tputs(tcaps->le, 1, &ft_putchar);
		input->prev_index = input->index--;
	}
	return (0);
}

/*
**	Here we will process the RIGHT key:
**	We use the termcap 'ri' to move the cursor a single case to the right,
**	but only if the cursor is not already at the end (otherwise it would result
**	in undefined behavior)
*/
int	process_key_right(const t_term *tcaps, t_input *input)
{
	if (input->index < input->prev_len)
	{
		tputs(tcaps->ri, 1, &ft_putchar);
		input->prev_index = input->index++;
	}
	return (0);
}

/*
**	Here we will process the UP/DOWN arrows:
**	For UP we will get the previous command in history if there is one, if not
**	it will just block and play a beep sound, same for DOWN, the only exception
**	is that when we are at the last element, we first set the input to an empty
**	string, and if DOWN is pressed again, then we will block and play the beep.
*/
int	process_key_hist(const t_list *history_sentinel, t_input *input, int key)
{
	if ((key == _KEY_DOWN) && input->hist->prev == history_sentinel)
	{
		if (reset_input(input, history_sentinel))
			return (-1);
	}
	else if (((key == _KEY_UP) && input->hist->next != history_sentinel)
		|| ((key == _KEY_DOWN) && input->hist != history_sentinel))
	{
		free(input->in);
		if (process_hist(key, input))
			return (-1);
	}
	else
		return (key_hist_block());
	return (0);
}
