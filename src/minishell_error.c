/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 21:35:37 by lsuardi           #+#    #+#             */
/*   Updated: 2021/03/29 00:40:55 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int minishell_error(void)
{
	perror("minishell");
	ft_clearenv();
	gb_load();
	gb_clear();
	return (-1);
}

int	parsing_error(char unexpected_token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putchar_fd(unexpected_token, 2);
	ft_putendl_fd("'", 2);
	return (-1);
}
