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

int	reset_input(t_input * input, const t_list * history)
{
	free(input->in);
	if (!(input->in = ft_strdup("")))
		return (-1);
	input->hist = (t_list*)history;
	input->prev_index = input->index;
	input->index = 0;
	return (0);
}

int	key_hist_block(void)
{
	ft_beep();
	return (1);
}

int	update_input(const t_term * tcaps, t_input * input)
{
	if (input->prev_index)
		tputs(tparm(tcaps->ile, input->prev_index), 1, ft_putchar);
	tputs(tcaps->ks, 1, ft_putchar);
	ft_putstr(input->in);
	if ((input->prev_len = ft_strlen(input->in)) != input->index)
		tputs(tparm(tcaps->ile, input->prev_len - input->index), 1, ft_putchar);
	return (0);
}
