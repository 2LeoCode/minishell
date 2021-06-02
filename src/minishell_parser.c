/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 18:23:04 by lsuardi           #+#    #+#             */
/*   Updated: 2021/04/03 22:48:34 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	next_token(char *input)
{
	t_token	token;

	if (ft_isspace(*input))
	{
		while (ft_isspace(*input))
			input++;
	}
	else
	{
		while (*input && !ft_memchr(";|<>", *input, 4))
			input++;
	}
	token.token_ptr = input;
	if (!*input)
		token.token_type = token_end;
	else if (*input == '<')
		token.token_type = token_arrow_left;
	else if (*input == '>' && input[1] == '>')
		token.token_type = token_double_arrow_left;
	else if (*input == '>')
		token.token_type = token_arrow_left;
	else if (*input == ';')
		token.token_type = token_semicolon;
	else if (*input == '|')
		token.token_type = token_pipe;
	else
		token.token_type = token_text;
	return (token);
}

int	minishell_parser(t_list *cmd_list, char *input)
{
	t_token	current_token;
	t_token	head_token;
	t_cmd	*actual;

	current_token = next_token(input);
	while (current_token.token_type != token_end)
	{
		input = current_token.token_ptr;
		if (current_token.token_type == token_double_arrow_right)
			input += 2;
		else if (current_token.token_type != token_end
				&& current_token.token_type != token_text)
			input++;
		if (current_token.token_type == token_text)

		head_token = next_token(input);
	}
}
