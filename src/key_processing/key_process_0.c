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

int	process_key_print(t_input *input, int key)
{
	if (ft_strinsert(&input->in, input->index, key, free))
		return (-1);
	input->prev_index = input->index++;
	return (0);
}

int	process_key_del(t_input *input)
{
	input->prev_index = input->index--;
	if (ft_strerase(&input->in, input->index, free))
		return (-1);
	return (0);
}

int	process_key_left(const t_term *tcaps, t_input *input)
{
	if (input->index > 0)
	{
		tputs(tcaps->le, 1, &ft_putchar);
		input->prev_index = input->index--;
	}
	return (0);
}

int	process_key_right(const t_term *tcaps, t_input *input)
{
	if (input->index < input->prev_len)
	{
		tputs(tcaps->ri, 1, &ft_putchar);
		input->prev_index = input->index++;
	}
	return (0);
}

int	process_key_hist(const t_list *history, t_input *input, int key)
{
	if (((key == _KEY_UP) && input->hist)
	|| ((key == _KEY_DOWN) && input->prev_hist))
	{
		if (key == _KEY_UP)
			input->prev_hist = input->hist->prev;
		else
		{
			input->hist = input->prev_hist;
			input->prev_hist = input->prev_hist->prev;
		}
		free(input->in);
		if (!(input->in = ft_strdup((char*)input->hist->data)))
			return (-1);
		input->prev_index = input->index;
		input->index = ft_strlen(input->in);
		input->hist = input->hist->next;
	}
	else if ((key == _KEY_DOWN) && *(input->in))
	{
		if (reset_input(input, history))
			return (-1);
	}
	else
		return (key_hist_block());
	return (0);
}
